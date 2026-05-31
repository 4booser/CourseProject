#include "repositories/group_repository.h"
#include "storage/json_storage.h"
#include <nlohmann/json.hpp>
#include <optional>
#include <algorithm>
#include "models.h"
#include <vector>

using json = nlohmann::json;

const std::string group_file_path = "Output/Groups.json";

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

static models::Group ParseGroup(const json& group_json)
{
    models::Group group{};

    group.id = ReadId(group_json);
    group.name = group_json.contains("name")
        ? group_json["name"].get<std::string>()
        : group_json["Name"].get<std::string>();
    group.course = group_json.contains("course")
        ? group_json["course"].get<unsigned short>()
        : group_json["Course"].get<unsigned short>();
    group.speciality = group_json.contains("speciality")
        ? group_json["speciality"].get<std::string>()
        : group_json["Speciality"].get<std::string>();

    return group;
}

static json BuildGroupJson(const models::Group& group)
{
    return {
        {"id", group.id},
        {"name", group.name},
        {"course", group.course},
        {"speciality", group.speciality}
    };
}

unsigned short GetLastGroupId()
{
    json groups = storage::ReadJsonArray(group_file_path);
    unsigned short max_id = 0;

    for (const auto& group_json : groups)
    {
        if (HasId(group_json))
        {
            max_id = std::max(max_id, ReadId(group_json));
        }
    }

    return max_id;
}

bool SaveGroup(models::Group& group)
{
    json groups = storage::ReadJsonArray(group_file_path);

    group.id = GetLastGroupId() + 1;
    groups.push_back(BuildGroupJson(group));

    return storage::WriteJsonArray(group_file_path, groups);
}

std::vector<models::Group> GetGroups()
{
    std::vector<models::Group> result;
    json groups = storage::ReadJsonArray(group_file_path);

    for (const auto& group_json : groups)
    {
        if (!HasId(group_json))
        {
            continue;
        }

        result.push_back(ParseGroup(group_json));
    }

    return result;
}

std::optional<models::Group> GetGroupById(unsigned short id)
{
    json groups = storage::ReadJsonArray(group_file_path);

    for (const auto& group_json : groups)
    {
        if (!HasId(group_json))
        {
            continue;
        }

        if (ReadId(group_json) == id)
        {
            return ParseGroup(group_json);
        }
    }

    return std::nullopt;
}

bool EditGroupById(const unsigned short& id, const models::Group& updated_group)
{
    json groups = storage::ReadJsonArray(group_file_path);
    bool was_updated = false;

    for (auto& group_json : groups)
    {
        if (HasId(group_json) && ReadId(group_json) == id)
        {
            models::Group group_to_save = updated_group;
            group_to_save.id = id;
            group_json = BuildGroupJson(group_to_save);
            was_updated = true;
            break;
        }
    }

    if (!was_updated)
    {
        return false;
    }

    return storage::WriteJsonArray(group_file_path, groups);
}

bool DeleteGroupById(const unsigned short& id)
{
    json groups = storage::ReadJsonArray(group_file_path);
    bool was_deleted = false;

    for (auto it = groups.begin(); it != groups.end(); ++it)
    {
        if (HasId(*it) && ReadId(*it) == id)
        {
            groups.erase(it);
            was_deleted = true;
            break;
        }
    }

    if (!was_deleted)
    {
        return false;
    }

    return storage::WriteJsonArray(group_file_path, groups);
}
