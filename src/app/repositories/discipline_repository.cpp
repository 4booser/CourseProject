#include "repositories/discipline_repository.h"
#include "storage/json_storage.h"
#include <nlohmann/json.hpp>
#include <optional>
#include <algorithm>
#include "models.h"
#include <vector>

using json = nlohmann::json;

const std::string discipline_file_path = "Output/Disciplines.json";

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

static models::Discipline ParseDiscipline(const json& discipline_json)
{
    models::Discipline discipline{};

    discipline.id = ReadId(discipline_json);
    discipline.name = discipline_json.contains("name")
        ? discipline_json["name"].get<std::string>()
        : discipline_json["Name"].get<std::string>();
    discipline.quota = discipline_json.contains("quota")
        ? discipline_json["quota"].get<unsigned int>()
        : discipline_json["Quota"].get<unsigned int>();

    return discipline;
}

static json BuildDisciplineJson(const models::Discipline& discipline)
{
    return {
        {"id", discipline.id},
        {"name", discipline.name},
        {"quota", discipline.quota}
    };
}

unsigned short GetLastDisciplineId()
{
    json disciplines = storage::ReadJsonArray(discipline_file_path);
    unsigned short max_id = 0;

    for (const auto& discipline_json : disciplines)
    {
        if (HasId(discipline_json))
        {
            max_id = std::max(max_id, ReadId(discipline_json));
        }
    }

    return max_id;
}

bool SaveDiscipline(models::Discipline& discipline)
{
    json disciplines = storage::ReadJsonArray(discipline_file_path);

    discipline.id = GetLastDisciplineId() + 1;
    disciplines.push_back(BuildDisciplineJson(discipline));

    return storage::WriteJsonArray(discipline_file_path, disciplines);
}

std::vector<models::Discipline> GetDisciplines()
{
    std::vector<models::Discipline> result;
    json disciplines = storage::ReadJsonArray(discipline_file_path);

    for (const auto& discipline_json : disciplines)
    {
        if (!HasId(discipline_json))
        {
            continue;
        }

        result.push_back(ParseDiscipline(discipline_json));
    }

    return result;
}

std::optional<models::Discipline> GetDisciplineById(unsigned short id)
{
    json disciplines = storage::ReadJsonArray(discipline_file_path);

    for (const auto& discipline_json : disciplines)
    {
        if (!HasId(discipline_json))
        {
            continue;
        }

        if (ReadId(discipline_json) == id)
        {
            return ParseDiscipline(discipline_json);
        }
    }

    return std::nullopt;
}

bool EditDisciplineById(const unsigned short& id, const models::Discipline& updated_discipline)
{
    json disciplines = storage::ReadJsonArray(discipline_file_path);
    bool was_updated = false;

    for (auto& discipline_json : disciplines)
    {
        if (HasId(discipline_json) && ReadId(discipline_json) == id)
        {
            models::Discipline discipline_to_save = updated_discipline;
            discipline_to_save.id = id;
            discipline_json = BuildDisciplineJson(discipline_to_save);
            was_updated = true;
            break;
        }
    }

    if (!was_updated)
    {
        return false;
    }

    return storage::WriteJsonArray(discipline_file_path, disciplines);
}

bool RemoveDisciplineById(const unsigned short& id)
{
    json disciplines = storage::ReadJsonArray(discipline_file_path);
    bool was_removed = false;

    for (auto it = disciplines.begin(); it != disciplines.end(); ++it)
    {
        if (HasId(*it) && ReadId(*it) == id)
        {
            disciplines.erase(it);
            was_removed = true;
            break;
        }
    }

    if (!was_removed)
    {
        return false;
    }

    return storage::WriteJsonArray(discipline_file_path, disciplines);
}
