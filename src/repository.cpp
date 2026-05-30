#include "models.h"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

void AddTeacher(Teacher teacher){
    json data ={
        {"Id", teacher.Id},
        {"FullName", teacher.FullName},
        {"DigitalCommission", teacher.DigitalCommission},
        {"Quota", teacher.Quota}
    };
    data.dump(2);
}
