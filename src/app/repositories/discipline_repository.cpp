#include "repositories/discipline_repository.h"
#include <nlohmann/json.hpp>
#include <fstream>
#include <filesystem>
#include <optional>
#include "models.h"
#include <vector>

using json = nlohmann::json;
namespace fs = std::filesystem;

const std::string discipline_file_path = "Output/Disciplines.json";

static json ReadDisciplinesJson()
{
    std::ifstream input_file(discipline_file_path);

    if (!input_file.is_open())
    {
        return json::array();
    }

    json disciplines;

    try
    {
        input_file >> disciplines;
    }
    catch (...)
    {
        return json::array();
    }

    if (!disciplines.is_array())
    {
        return json::array();
    }

    return disciplines;
}

static bool WriteDisciplinesJson(const json& disciplines)
{
    fs::path path(discipline_file_path);
    fs::create_directories(path.parent_path());

    std::ofstream output_file(discipline_file_path);

    if (!output_file.is_open())
    {
        return false;
    }

    output_file << disciplines.dump(2);
    return true;
}

unsigned short GetLastDisciplineId()
{
    json disciplines = ReadDisciplinesJson();

    if (disciplines.empty())
    {
        return 0;
    }

    const auto& last_discipline = disciplines.back();

    if (!last_discipline.contains("Id"))
    {
        return 0;
    }

    return last_discipline["Id"].get<unsigned short>();
}

bool SaveDiscipline(models::Discipline& discipline)
{
    json disciplines = ReadDisciplinesJson();

    discipline.id = GetLastDisciplineId() + 1;

    json discipline_json = {
        {"Id", discipline.id},
        {"Name", discipline.name},
        {"Quota", discipline.quota}
    };

    disciplines.push_back(discipline_json);

    return WriteDisciplinesJson(disciplines);
}

std::vector<models::Discipline> GetDisciplines()
{
    std::vector<models::Discipline> result;
    json disciplines = ReadDisciplinesJson();

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
    json disciplines = ReadDisciplinesJson();

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
    json disciplines = ReadDisciplinesJson();
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

    return WriteDisciplinesJson(disciplines);
}

bool RemoveDisciplineById(const unsigned short& id)
{
    json disciplines = ReadDisciplinesJson();
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

    return WriteDisciplinesJson(disciplines);
}
