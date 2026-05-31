#include "repositories/teacher_repository.h"
#include "storage/json_storage.h"
#include <nlohmann/json.hpp>
#include <optional>
#include <algorithm>
#include "models.h"
#include <vector>

using json = nlohmann::json;

const std::string file_path = "Output/Teachers.json";

static bool HasId(const json& object)
{
    return object.contains("id") || object.contains("Id");
}

static unsigned short ReadId(const json& object)
{
    if (object.contains("id"))
    {
        return object["id"].get<unsigned short>();
    }

    return object["Id"].get<unsigned short>();
}

static models::Teacher ParseTeacher(const json& teacher_json)
{
    models::Teacher teacher{};

    teacher.id = ReadId(teacher_json);
    teacher.full_name = teacher_json.contains("full_name")
        ? teacher_json["full_name"].get<std::string>()
        : teacher_json["FullName"].get<std::string>();
    teacher.digital_commission = teacher_json.contains("digital_commission")
        ? teacher_json["digital_commission"].get<std::string>()
        : teacher_json["DigitalCommission"].get<std::string>();
    teacher.quota = teacher_json.contains("quota")
        ? teacher_json["quota"].get<unsigned int>()
        : teacher_json["Quota"].get<unsigned int>();

    return teacher;
}

static json BuildTeacherJson(const models::Teacher& teacher)
{
    return {
        {"id", teacher.id},
        {"full_name", teacher.full_name},
        {"digital_commission", teacher.digital_commission},
        {"quota", teacher.quota}
    };
}

unsigned short GetLastTeacherId()
{
    json teachers = storage::ReadJsonArray(file_path);
    unsigned short max_id = 0;

    for (const auto& teacher_json : teachers)
    {
        if (HasId(teacher_json))
        {
            max_id = std::max(max_id, ReadId(teacher_json));
        }
    }

    return max_id;
}

OperationResult SaveTeacher(models::Teacher& teacher)
{
    json teachers = storage::ReadJsonArray(file_path);

    teacher.id = GetLastTeacherId() + 1;
    teachers.push_back(BuildTeacherJson(teacher));

    if (!storage::WriteJsonArray(file_path, teachers))
    {
        return OperationResult::Fail("Не вдалося записати файл викладачiв.");
    }

    return OperationResult::Ok();
}

std::optional<models::Teacher> GetTeacherById(unsigned short id)
{
    json teachers = storage::ReadJsonArray(file_path);

    for (const auto& teacher_json : teachers)
    {
        if (!HasId(teacher_json))
        {
            continue;
        }

        if (ReadId(teacher_json) == id)
        {
            return ParseTeacher(teacher_json);
        }
    }

    return std::nullopt;
}

OperationResult EditTeacherById(const unsigned short& id, const models::Teacher& updated_teacher)
{
    json teachers = storage::ReadJsonArray(file_path);
    bool was_updated = false;

    for (auto& teacher_json : teachers)
    {
        if (HasId(teacher_json) && ReadId(teacher_json) == id)
        {
            models::Teacher teacher_to_save = updated_teacher;
            teacher_to_save.id = id;
            teacher_json = BuildTeacherJson(teacher_to_save);
            was_updated = true;
            break;
        }
    }

    if (!was_updated)
    {
        return OperationResult::Fail("Викладача з таким Id не знайдено.");
    }

    if (!storage::WriteJsonArray(file_path, teachers))
    {
        return OperationResult::Fail("Не вдалося записати файл викладачiв.");
    }

    return OperationResult::Ok();
}

OperationResult DeleteTeacherById(const unsigned short& id)
{
    json teachers = storage::ReadJsonArray(file_path);
    bool was_deleted = false;

    for (auto it = teachers.begin(); it != teachers.end(); ++it)
    {
        if (HasId(*it) && ReadId(*it) == id)
        {
            teachers.erase(it);
            was_deleted = true;
            break;
        }
    }

    if (!was_deleted)
    {
        return OperationResult::Fail("Викладача з таким Id не знайдено.");
    }

    if (!storage::WriteJsonArray(file_path, teachers))
    {
        return OperationResult::Fail("Не вдалося записати файл викладачiв.");
    }

    return OperationResult::Ok();
}
