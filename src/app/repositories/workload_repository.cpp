#include "headers/workload_repository.h"
#include <nlohmann/json.hpp>
#include <ofstream>
#include "models.h"
#include <vector>

using json = nlohmann::json;

void SaveWorkload(Workload workload){
    json data ={
        {"Id", workload.Id},
        {"TeachersIds", workload.TeachersIds},
        {"SubjectId", workload.SubjectId},
        {"GroupsId", workload.GroupsIds},
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
    data.dump(2);
}
