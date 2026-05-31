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

    if (!input_file.is_open())
    {
        return 1;
    }

    json teachers;

    try
    {
        input_file >> teachers;
    }
    catch (...)
    {
        return 1;
    }

    if (!teachers.is_array() || teachers.empty())
    {
        return 1;
    }

    const auto& last_teacher = teachers.back();

    if (!last_teacher.contains("Id"))
    {
        return 1;
    }

    return last_teacher["Id"].get<unsigned short>() + 1;
}

bool SaveTeacher(models::Teacher& teacher){
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

    teacher.id = GetNextTeacherId();

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