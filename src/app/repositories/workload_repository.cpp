#include "include/repository_headers/workload_repository.h"
#include <nlohmann/json.hpp>
#include <fstream>
#include "models.h"
#include <vector>

using json = nlohmann::json;

void SaveWorkload(const Workload& workload){
    json data ={
        {"Id", workload.Id},
        {"TeachersIds", workload.TeacherIds},
        {"SubjectId", workload.SubjectId},
        {"GroupsId", workload.GroupIds},
        {"Lectures", workload.Lectures},
        {"PracticalClasses", workload.PracticalClasses},
        {"LaboratoryClasses", workload.LaboratoryClasses},
        {"Seminars", workload.Seminars},
        {"Consultations", workload.Consultations},
        {"TotalHours", workload.TotalHours}
    };
    std::ofstream file("Workloads.json");

    if (!file.is_open())
    {
        return;
    }
    file << data.dump(2);
}
