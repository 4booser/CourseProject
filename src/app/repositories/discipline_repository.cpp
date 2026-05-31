#include "repositories/discipline_repository.h"
#include "storage/json_storage.h"
#include <nlohmann/json.hpp>
#include <optional>
#include <algorithm>
#include "models.h"
#include <vector>

using json = nlohmann::json;

const std::string discipline_file_path = "Output/Disciplines.json";

unsigned short GetLastDisciplineId()
{
    json disciplines = storage::ReadJsonArray(discipline_file_path);
    unsigned short max_id = 0;

    for (const auto& discipline_json : disciplines)
    {
        if (discipline_json.contains("Id"))
        {
            max_id = std::max(max_id, discipline_json["Id"].get<unsigned short>());
        }
    }

    return max_id;
}

bool SaveDiscipline(models::Discipline& discipline)
{
    json disciplines = storage::ReadJsonArray(discipline_file_path);

    discipline.id = GetLastDisciplineId() + 1;

    json discipline_json = {
        {"Id", discipline.id},
        {"Name", discipline.name},
        {"Quota", discipline.quota}
    };

    disciplines.push_back(discipline_json);

    return storage::WriteJsonArray(discipline_file_path, disciplines);
}

std::vector<models::Discipline> GetDisciplines()
{
    std::vector<models::Discipline> result;
    json disciplines = storage::ReadJsonArray(discipline_file_path);

    for (const auto& discipline_json : disciplines)
    {
        if (!discipline_json.contains("Id"))
        {
            continue;
        }

        models::Discipline discipline;
        discipline.id = discipline_json["Id"].get<unsigned short>();
        discipline.name = discipline_json["Name"].get<std::string>();
        discipline.quota = discipline_json["Quota"].get<unsigned int>();

        result.push_back(discipline);
    }

    return result;
}

std::optional<models::Discipline> GetDisciplineById(unsigned short id)
{
    json disciplines = storage::ReadJsonArray(discipline_file_path);

    for (const auto& discipline_json : disciplines)
    {
        if (!discipline_json.contains("Id"))
        {
            continue;
        }

        if (discipline_json["Id"].get<unsigned short>() == id)
        {
            models::Discipline discipline;
            discipline.id = discipline_json["Id"].get<unsigned short>();
            discipline.name = discipline_json["Name"].get<std::string>();
            discipline.quota = discipline_json["Quota"].get<unsigned int>();

            return discipline;
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
        if (discipline_json.contains("Id") && discipline_json["Id"].get<unsigned short>() == id)
        {
            discipline_json["Name"] = updated_discipline.name;
            discipline_json["Quota"] = updated_discipline.quota;
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
        if (it->contains("Id") && (*it)["Id"].get<unsigned short>() == id)
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
