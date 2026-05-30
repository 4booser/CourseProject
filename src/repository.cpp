#include "models.h"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

void SaveTeacher(Teacher teacher){
    json data ={
        {"Id", teacher.Id},
        {"FullName", teacher.FullName},
        {"DigitalComission", teacher.DigitialCommission},
        {"Quota", teacher.Quota}
    };
    data.dump(2);
}
