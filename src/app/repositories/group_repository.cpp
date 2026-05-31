#include "repositories/group_repository.h"
#include <nlohmann/json.hpp>
#include <fstream>
#include <filesystem>
#include <optional>
#include <algorithm>
#include "models.h"
#include <vector>

using json = nlohmann::json;
namespace fs = std::filesystem;

const std::string group_file_path = "Output/Groups.json";

static json ReadGroupsJson()
{
    std::ifstream input_file(group_file_path);

    if (!input_file.is_open())
    {
        return json::array();
    }

    json groups;

    try
    {
        input_file >> groups;
    }
    catch (...)
    {
        return json::array();
    }

    if (!groups.is_array())
    {
        return json::array();
    }

    return groups;
}

static bool WriteGroupsJson(const json& groups)
{
    fs::path path(group_file_path);
    fs::create_directories(path.parent_path());

    std::ofstream output_file(group_file_path);

    if (!output_file.is_open())
    {
        return false;
    }

    output_file << groups.dump(2);
    return true;
}

unsigned short GetLastGroupId()
{
    json groups = ReadGroupsJson();
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
    json groups = ReadGroupsJson();

    group.id = GetLastGroupId() + 1;

    json group_json = {
        {"Id", group.id},
        {"Name", group.name},
        {"Course", group.course},
        {"Speciality", group.speciality}
    };

    groups.push_back(group_json);

    return WriteGroupsJson(groups);
}

std::vector<models::Group> GetGroups()
{
    std::vector<models::Group> result;
    json groups = ReadGroupsJson();

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
    json groups = ReadGroupsJson();

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
    json groups = ReadGroupsJson();
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

    return WriteGroupsJson(groups);
}

bool DeleteGroupById(const unsigned short& id)
{
    json groups = ReadGroupsJson();
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

    return WriteGroupsJson(groups);
}
