#include "repositories/teacher_repository.h"
#include <nlohmann/json.hpp>
#include <fstream>
#include <filesystem>
#include <optional>
#include <algorithm>
#include "models.h"
#include <vector>

using json = nlohmann::json;
namespace fs = std::filesystem;

const std::string file_path = "Output/Teachers.json";

unsigned short GetLastTeacherId()
{
    std::ifstream input_file(file_path);

    if (!input_file.is_open())
    {
        return 0;
    }

    json teachers;

    try
    {
        input_file >> teachers;
    }
    catch (...)
    {
        return 0;
    }

    if (!teachers.is_array() || teachers.empty())
    {
        return 0;
    }

    unsigned short max_id = 0;

    for (const auto& teacher_json : teachers)
    {
        if (teacher_json.contains("Id"))
        {
            max_id = std::max(max_id, teacher_json["Id"].get<unsigned short>());
        }
    }

    return max_id;
}

bool SaveTeacher(models::Teacher& teacher)
{
    json teachers = json::array();

    fs::path path(file_path);
    fs::create_directories(path.parent_path());

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

        input_file.close();
    }

    teacher.id = GetLastTeacherId() + 1;

    json teacher_json = {
        {"Id", teacher.id},
        {"FullName", teacher.full_name},
        {"DigitalCommission", teacher.digital_commission},
        {"Quota", teacher.quota}
    };

    teachers.push_back(teacher_json);

    std::ofstream output_file(file_path);

    if (!output_file.is_open())
    {
        return false;
    }

    output_file << teachers.dump(2);
    return true;
}

std::optional<models::Teacher> GetTeacherById(unsigned short id)
{
    std::ifstream input_file(file_path);

    if (!input_file.is_open()){ return std::nullopt; }

    json teachers;

    try{ input_file >> teachers; }
    catch (...){  return std::nullopt; }

    if (!teachers.is_array()) { return std::nullopt; }

    for (const auto& teacher_json : teachers)
    {
        if (!teacher_json.contains("Id")){
            continue;
        }

        if (teacher_json["Id"].get<unsigned short>() == id){
            models::Teacher teacher;

            teacher.id = teacher_json["Id"].get<unsigned short>();
            teacher.full_name = teacher_json["FullName"].get<std::string>();
            teacher.digital_commission = teacher_json["DigitalCommission"].get<std::string>();
            teacher.quota = teacher_json["Quota"].get<unsigned int>();

            return teacher;
        }
    }
    return std::nullopt;
}

bool EditTeacherById(const unsigned short& id, const models::Teacher& updated_teacher)
{
    std::ifstream input_file(file_path);

    if (!input_file.is_open())
    {
        return false;
    }

    json teachers;

    try
    {
        input_file >> teachers;
    }
    catch (...)
    {
        return false;
    }

    input_file.close();

    if (!teachers.is_array())
    {
        return false;
    }

    bool was_updated = false;

    for (auto& teacher_json : teachers)
    {
        if (teacher_json.contains("Id") && teacher_json["Id"].get<unsigned short>() == id)
        {
            teacher_json["FullName"] = updated_teacher.full_name;
            teacher_json["DigitalCommission"] = updated_teacher.digital_commission;
            teacher_json["Quota"] = updated_teacher.quota;
            was_updated = true;
            break;
        }
    }

    if (!was_updated)
    {
        return false;
    }

    std::ofstream output_file(file_path);

    if (!output_file.is_open())
    {
        return false;
    }

    output_file << teachers.dump(2);
    return true;
}

bool DeleteTeacherById(const unsigned short& id)
{
    std::ifstream input_file(file_path);

    if (!input_file.is_open())
    {
        return false;
    }

    json teachers;

    try
    {
        input_file >> teachers;
    }
    catch (...)
    {
        return false;
    }

    input_file.close();

    if (!teachers.is_array())
    {
        return false;
    }

    bool was_deleted = false;

    for (auto it = teachers.begin(); it != teachers.end(); ++it)
    {
        if (it->contains("Id") && (*it)["Id"].get<unsigned short>() == id)
        {
            teachers.erase(it);
            was_deleted = true;
            break;
        }
    }

    if (!was_deleted)
    {
        return false;
    }

    std::ofstream output_file(file_path);

    if (!output_file.is_open())
    {
        return false;
    }

    output_file << teachers.dump(2);
    return true;
}
