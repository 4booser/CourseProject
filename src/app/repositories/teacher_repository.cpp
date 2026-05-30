#include "repositories/teacher_repository.h"
#include <nlohmann/json.hpp>
#include <fstream>
#include "models.h"
#include <vector>

using json = nlohmann::json;

const std::string file_path = "Output/Teachers.json";

void SaveTeacher(const models::Teacher& teacher){
    json teachers = json::array();


    std::ifstream input_file(file_path);

    if (input_file.is_open())
    {
        try
        {
            input_file >> teachers;

            if (!teachers.is_array())
            {
                teachers = json::array();
            }
        }
        catch (...)
        {
            teachers = json::array();
        }
    }

    json teacher_json ={
        {"Id", teacher.Id},
        {"FullName", teacher.FullName},
        {"DigitalCommission", teacher.DigitalCommission},
        {"Quota", teacher.Quota}
    };

    teachers.push_back(teacher_json);

    std::ofstream output_file(file_path);

    if (!output_file.is_open())
    {
        return;
    }

    output_file << teachers.dump(2);
}