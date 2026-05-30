#include "repositories/teacher_repository.h"
#include <nlohmann/json.hpp>
#include <fstream>
#include "models.h"
#include <vector>

using json = nlohmann::json;

const std::string file_path = "Output/Teachers.json";

unsigned short GetNextTeacherId()
{
    std::ifstream input_file(file_path);

    if (!input_file.is_open()){ return 1; }

    json teachers;

    try{
        input_file >> teachers;
    }
    catch (...) { return 1; }

    if (!teachers.is_array() || teachers.empty()) { return 1; }

    unsigned short max_id = 0;

    for (const auto& teacher : teachers)
    {
        if (teacher.contains("Id") && teacher["Id"].is_number_unsigned())
        {
            unsigned short id = teacher["Id"].get<unsigned short>();

            if (id > max_id)
            {
                max_id = id;
            }
        }
    }

    return max_id + 1;
}

bool SaveTeacher(const models::Teacher& teacher){
    json teachers = json::array();

    std::ifstream input_file(file_path);

    if (!input_file.is_open()) { return false; }

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

    json teacher_json ={
        {"Id", teacher.id},
        {"FullName", teacher.full_name},
        {"DigitalCommission", teacher.digital_commission},
        {"Quota", teacher.quota}
    };

    teachers.push_back(teacher_json);

    std::ofstream output_file(file_path);

    if (!output_file.is_open()){ return false;}

    output_file << teachers.dump(2);
    return true;
}