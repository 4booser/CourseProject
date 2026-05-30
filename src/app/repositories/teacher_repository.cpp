#include "include/repository_headers/teacher_repository.h"
#include <nlohmann/json.hpp>
#include <fstream>
#include "models.h"
#include <vector>

using json = nlohmann::json;

void SaveTeacher(const Teacher& teacher){
    json data ={
        {"Id", teacher.Id},
        {"FullName", teacher.FullName},
        {"DigitalCommission", teacher.DigitalCommission},
        {"Quota", teacher.Quota}
    };
    std::ofstream file("Teachers.json");

    if (!file.is_open())
    {
        return;
    }
    file << data.dump(2);
}