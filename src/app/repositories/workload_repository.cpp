#include "repositories/workload_repository.h"
#include <nlohmann/json.hpp>
#include <fstream>
#include "models.h"
#include <vector>

using json = nlohmann::json;

bool SaveWorkload(models::Workload& workload){
    json data ={
        {"Id", workload.id},
        {"TeachersIds", workload.teacher_ids},
        {"SubjectId", workload.subject_id},
        {"GroupsId", workload.group_ids},
        {"Lectures", workload.lectures},
        {"PracticalClasses", workload.practical_classes},
        {"LaboratoryClasses", workload.laboratory_classes},
        {"Seminars", workload.seminars},
        {"Consultations", workload.consultations},
        {"TotalHours", workload.total_hours}
    };
    std::ofstream file("Workloads.json");

    if (!file.is_open()) { return false; }
    file << data.dump(2);
    return true;
}
