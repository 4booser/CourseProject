#include "repositories/group_repository.h"
#include "storage/json_storage.h"
#include <nlohmann/json.hpp>
#include <optional>
#include <algorithm>
#include "models.h"
#include <vector>

using json = nlohmann::json;

const std::string group_file_path = "Output/Groups.json";

unsigned short GetLastGroupId()
{
    json groups = storage::ReadJsonArray(group_file_path);
    unsigned short max_id = 0;

    for (const auto& group_json : groups)
    {
        if (group_json.contains("Id"))
        {
            max_id = std::max(max_id, group_json["Id"].get<unsigned short>());
        }
    }

    return max_id;
}

bool SaveGroup(models::Group& group)
{
    json groups = storage::ReadJsonArray(group_file_path);

    group.id = GetLastGroupId() + 1;

    json group_json = {
        {"Id", group.id},
        {"Name", group.name},
        {"Course", group.course},
        {"Speciality", group.speciality}
    };

    groups.push_back(group_json);

    return storage::WriteJsonArray(group_file_path, groups);
}

std::vector<models::Group> GetGroups()
{
    std::vector<models::Group> result;
    json groups = storage::ReadJsonArray(group_file_path);

    for (const auto& group_json : groups)
    {
        if (!group_json.contains("Id"))
        {
            continue;
        }

        models::Group group;
        group.id = group_json["Id"].get<unsigned short>();
        group.name = group_json["Name"].get<std::string>();
        group.course = group_json["Course"].get<unsigned short>();
        group.speciality = group_json["Speciality"].get<std::string>();

        result.push_back(group);
    }

    return result;
}

std::optional<models::Group> GetGroupById(unsigned short id)
{
    json groups = storage::ReadJsonArray(group_file_path);

    for (const auto& group_json : groups)
    {
        if (!group_json.contains("Id"))
        {
            continue;
        }

        if (group_json["Id"].get<unsigned short>() == id)
        {
            models::Group group;
            group.id = group_json["Id"].get<unsigned short>();
            group.name = group_json["Name"].get<std::string>();
            group.course = group_json["Course"].get<unsigned short>();
            group.speciality = group_json["Speciality"].get<std::string>();

            return group;
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
        if (group_json.contains("Id") && group_json["Id"].get<unsigned short>() == id)
        {
            group_json["Name"] = updated_group.name;
            group_json["Course"] = updated_group.course;
            group_json["Speciality"] = updated_group.speciality;
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
        if (it->contains("Id") && (*it)["Id"].get<unsigned short>() == id)
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
