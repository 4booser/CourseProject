#include "repositories/workload_repository.h"
#include "storage/json_storage.h"
#include <nlohmann/json.hpp>
#include <optional>
#include <algorithm>
#include "models.h"
#include <vector>

using json = nlohmann::json;

const std::string workload_file_path = "Output/Workloads.json";

static models::Workload ParseWorkload(const json& workload_json)
{
    models::Workload workload{};

    workload.id = workload_json["Id"].get<unsigned short>();
    workload.teacher_ids = workload_json["TeachersIds"].get<std::vector<unsigned short>>();
    workload.group_ids = workload_json["GroupIds"].get<std::vector<unsigned short>>();

    if (workload_json.contains("DisciplineId"))
    {
        workload.discipline_id = workload_json["DisciplineId"].get<unsigned short>();
    }
    else if (workload_json.contains("SubjectId"))
    {
        workload.discipline_id = workload_json["SubjectId"].get<unsigned short>();
    }

    workload.lectures = workload_json["Lectures"].get<unsigned int>();
    workload.practical_classes = workload_json["PracticalClasses"].get<unsigned int>();
    workload.laboratory_classes = workload_json["LaboratoryClasses"].get<unsigned int>();
    workload.seminars = workload_json["Seminars"].get<unsigned int>();
    workload.consultations = workload_json["Consultations"].get<unsigned int>();
    workload.total_hours = workload_json["TotalHours"].get<unsigned int>();

    return workload;
}

static json BuildWorkloadJson(const models::Workload& workload)
{
    return {
        {"Id", workload.id},
        {"TeachersIds", workload.teacher_ids},
        {"GroupIds", workload.group_ids},
        {"DisciplineId", workload.discipline_id},
        {"Lectures", workload.lectures},
        {"PracticalClasses", workload.practical_classes},
        {"LaboratoryClasses", workload.laboratory_classes},
        {"Seminars", workload.seminars},
        {"Consultations", workload.consultations},
        {"TotalHours", workload.total_hours}
    };
}

unsigned short GetLastWorkloadId()
{
    json workloads = storage::ReadJsonArray(workload_file_path);
    unsigned short max_id = 0;

    for (const auto& workload_json : workloads)
    {
        if (workload_json.contains("Id"))
        {
            max_id = std::max(max_id, workload_json["Id"].get<unsigned short>());
        }
    }

    return max_id;
}

bool SaveWorkload(models::Workload& workload)
{
    json workloads = storage::ReadJsonArray(workload_file_path);

    workload.id = GetLastWorkloadId() + 1;

    workloads.push_back(BuildWorkloadJson(workload));

    return storage::WriteJsonArray(workload_file_path, workloads);
}

std::vector<models::Workload> GetWorkloads()
{
    std::vector<models::Workload> result;
    json workloads = storage::ReadJsonArray(workload_file_path);

    for (const auto& workload_json : workloads)
    {
        if (!workload_json.contains("Id"))
        {
            continue;
        }

        result.push_back(ParseWorkload(workload_json));
    }

    return result;
}

std::optional<models::Workload> GetWorkloadById(unsigned short id)
{
    json workloads = storage::ReadJsonArray(workload_file_path);

    for (const auto& workload_json : workloads)
    {
        if (!workload_json.contains("Id"))
        {
            continue;
        }

        if (workload_json["Id"].get<unsigned short>() == id)
        {
            return ParseWorkload(workload_json);
        }
    }

    return std::nullopt;
}

bool EditWorkloadById(const unsigned short& id, const models::Workload& updated_workload)
{
    json workloads = storage::ReadJsonArray(workload_file_path);
    bool was_updated = false;

    for (auto& workload_json : workloads)
    {
        if (workload_json.contains("Id") && workload_json["Id"].get<unsigned short>() == id)
        {
            models::Workload workload_to_save = updated_workload;
            workload_to_save.id = id;
            workload_json = BuildWorkloadJson(workload_to_save);
            was_updated = true;
            break;
        }
    }

    if (!was_updated)
    {
        return false;
    }

    return storage::WriteJsonArray(workload_file_path, workloads);
}

bool RemoveWorkloadById(const unsigned short& id)
{
    json workloads = storage::ReadJsonArray(workload_file_path);
    bool was_removed = false;

    for (auto it = workloads.begin(); it != workloads.end(); ++it)
    {
        if (it->contains("Id") && (*it)["Id"].get<unsigned short>() == id)
        {
            workloads.erase(it);
            was_removed = true;
            break;
        }
    }

    if (!was_removed)
    {
        return false;
    }

    return storage::WriteJsonArray(workload_file_path, workloads);
}
