#include "headers/teacher_repository.h"
#include <nlohmann/json.hpp>
#include <ofstream>
#include "models.h"
#include <vector>

using json = nlohmann::json;

void SaveTeacher(Teacher teacher){
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
    data.dump(2);
}