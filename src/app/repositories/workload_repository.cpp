#include "repositories/workload_repository.h"
#include <nlohmann/json.hpp>
#include <fstream>
#include "models.h"
#include <vector>

using json = nlohmann::json;
namespace fs = std::filesystem;

const std::string file_path = "Output/Workloads.json";

unsigned short GetLastWorkloadId()
{
    std::ifstream input_file(file_path);

    if (!input_file.is_open()) { return 1; }

    json workloads;

    try{ input_file >> workloads; }
    catch (...){ return 1; }

    if (!workloads.is_array() || workloads.empty()) { return 1; }

    const auto& last_workload = workloads.back();

    if (!last_workload.contains("Id")) { return 1; }

    return last_workload["Id"].get<unsigned short>();
}

bool SaveWorkload(models::Workload& workload)
{
    json workloads = json::array();

    fs::path path(file_path);
    fs::create_directories(path.parent_path());

    std::ifstream input_file(file_path);

    if (input_file.is_open())
    {
        try
        {
            input_file >> workloads;

            if (!workloads.is_array())
            {
                workloads = json::array();
            }
        }
        catch (...)
        {
            workloads = json::array();
        }

        input_file.close();
    }

    workload.id = GetLastWorkloadId() + 1;

    json workload_json = {
        {"Id", workload.id},
        {"TeachersIds", workload.teacher_ids},
        {"GroupIds", workload.group_ids},
        {"SubjectId", workload.subject_id},
        {"Lectures", workload.lectures},
        {"PracticalClasses", workload.practical_classes},
        {"LaboratoryClasses", workload.laboratory_classes},
        {"Seminars", workload.seminars},
        {"Consultations", workload.consultations},
        {"TotalHours", workload.total_hours}
    };

    workloads.push_back(workload_json);

    std::ofstream output_file(file_path);

    if (!output_file.is_open())
    {
        return false;
    }

    output_file << workloads.dump(2);
    return true;
}
