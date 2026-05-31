#include "repositories/teacher_repository.h"
#include "storage/json_storage.h"
#include <nlohmann/json.hpp>
#include <optional>
#include <algorithm>
#include "models.h"
#include <vector>

using json = nlohmann::json;

const std::string file_path = "Output/Teachers.json";

unsigned short GetLastTeacherId()
{
    json teachers = storage::ReadJsonArray(file_path);
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
    json teachers = storage::ReadJsonArray(file_path);

    teacher.id = GetLastTeacherId() + 1;

    json teacher_json = {
        {"Id", teacher.id},
        {"FullName", teacher.full_name},
        {"DigitalCommission", teacher.digital_commission},
        {"Quota", teacher.quota}
    };

    teachers.push_back(teacher_json);

    return storage::WriteJsonArray(file_path, teachers);
}

std::optional<models::Teacher> GetTeacherById(unsigned short id)
{
    json teachers = storage::ReadJsonArray(file_path);

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
    json teachers = storage::ReadJsonArray(file_path);
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

    return storage::WriteJsonArray(file_path, teachers);
}

bool DeleteTeacherById(const unsigned short& id)
{
    json teachers = storage::ReadJsonArray(file_path);
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

    return storage::WriteJsonArray(file_path, teachers);
}
