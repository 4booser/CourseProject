#include "repositories/workload_repository.h"
#include "storage/json_storage.h"
#include <nlohmann/json.hpp>
#include <optional>
#include <algorithm>
#include "models.h"
#include <vector>

using json = nlohmann::json;

const std::string workload_file_path = "Output/Workloads.json";

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

template <typename T>
static T ReadField(const json& object, const char* snake_case_key, const char* pascal_case_key)
{
    if (object.contains(snake_case_key))
    {
        return object[snake_case_key].get<T>();
    }

    return object[pascal_case_key].get<T>();
}

static models::Workload ParseWorkload(const json& workload_json)
{
    models::Workload workload{};

    workload.id = ReadId(workload_json);
    workload.teacher_ids = ReadField<std::vector<unsigned short>>(workload_json, "teacher_ids", "TeachersIds");
    workload.group_ids = ReadField<std::vector<unsigned short>>(workload_json, "group_ids", "GroupIds");

    if (workload_json.contains("discipline_id"))
    {
        workload.discipline_id = workload_json["discipline_id"].get<unsigned short>();
    }
    else if (workload_json.contains("DisciplineId"))
    {
        workload.discipline_id = workload_json["DisciplineId"].get<unsigned short>();
    }
    else if (workload_json.contains("SubjectId"))
    {
        workload.discipline_id = workload_json["SubjectId"].get<unsigned short>();
    }

    workload.lectures = ReadField<unsigned int>(workload_json, "lectures", "Lectures");
    workload.practical_classes = ReadField<unsigned int>(workload_json, "practical_classes", "PracticalClasses");
    workload.laboratory_classes = ReadField<unsigned int>(workload_json, "laboratory_classes", "LaboratoryClasses");
    workload.seminars = ReadField<unsigned int>(workload_json, "seminars", "Seminars");
    workload.consultations = ReadField<unsigned int>(workload_json, "consultations", "Consultations");
    workload.total_hours = ReadField<unsigned int>(workload_json, "total_hours", "TotalHours");

    return workload;
}

static json BuildWorkloadJson(const models::Workload& workload)
{
    return {
        {"id", workload.id},
        {"teacher_ids", workload.teacher_ids},
        {"group_ids", workload.group_ids},
        {"discipline_id", workload.discipline_id},
        {"lectures", workload.lectures},
        {"practical_classes", workload.practical_classes},
        {"laboratory_classes", workload.laboratory_classes},
        {"seminars", workload.seminars},
        {"consultations", workload.consultations},
        {"total_hours", workload.total_hours}
    };
}

unsigned short GetLastWorkloadId()
{
    json workloads = storage::ReadJsonArray(workload_file_path);
    unsigned short max_id = 0;

    for (const auto& workload_json : workloads)
    {
        if (HasId(workload_json))
        {
            max_id = std::max(max_id, ReadId(workload_json));
        }
    }

    return max_id;
}

bool SaveWorkload(models::Workload& workload)
{
    json workloads = storage::ReadJsonArray(workload_file_path);

    workload.id = GetLastWorkloadId() + 1;
    workloads.push_back(BuildWorkloadJson(workload));

    return storage::WriteJsonArray(workload_file_path, workloads);
}

std::vector<models::Workload> GetWorkloads()
{
    std::vector<models::Workload> result;
    json workloads = storage::ReadJsonArray(workload_file_path);

    for (const auto& workload_json : workloads)
    {
        if (!HasId(workload_json))
        {
            continue;
        }

        result.push_back(ParseWorkload(workload_json));
    }

    return result;
}

std::optional<models::Workload> GetWorkloadById(unsigned short id)
{
    json workloads = storage::ReadJsonArray(workload_file_path);

    for (const auto& workload_json : workloads)
    {
        if (!HasId(workload_json))
        {
            continue;
        }

        if (ReadId(workload_json) == id)
        {
            return ParseWorkload(workload_json);
        }
    }

    return std::nullopt;
}

bool EditWorkloadById(const unsigned short& id, const models::Workload& updated_workload)
{
    json workloads = storage::ReadJsonArray(workload_file_path);
    bool was_updated = false;

    for (auto& workload_json : workloads)
    {
        if (HasId(workload_json) && ReadId(workload_json) == id)
        {
            models::Workload workload_to_save = updated_workload;
            workload_to_save.id = id;
            workload_json = BuildWorkloadJson(workload_to_save);
            was_updated = true;
            break;
        }
    }

    if (!was_updated)
    {
        return false;
    }

    return storage::WriteJsonArray(workload_file_path, workloads);
}

bool RemoveWorkloadById(const unsigned short& id)
{
    json workloads = storage::ReadJsonArray(workload_file_path);
    bool was_removed = false;

    for (auto it = workloads.begin(); it != workloads.end(); ++it)
    {
        if (HasId(*it) && ReadId(*it) == id)
        {
            workloads.erase(it);
            was_removed = true;
            break;
        }
    }

    if (!was_removed)
    {
        return false;
    }

    return storage::WriteJsonArray(workload_file_path, workloads);
}

bool HasWorkloadForTeacher(unsigned short teacher_id)
{
    std::vector<models::Workload> workloads = GetWorkloads();

    for (const models::Workload& workload : workloads)
    {
        if (std::find(workload.teacher_ids.begin(), workload.teacher_ids.end(), teacher_id) != workload.teacher_ids.end())
        {
            return true;
        }
    }

    return false;
}

bool HasWorkloadForGroup(unsigned short group_id)
{
    std::vector<models::Workload> workloads = GetWorkloads();

    for (const models::Workload& workload : workloads)
    {
        if (std::find(workload.group_ids.begin(), workload.group_ids.end(), group_id) != workload.group_ids.end())
        {
            return true;
        }
    }

    return false;
}

bool HasWorkloadForDiscipline(unsigned short discipline_id)
{
    std::vector<models::Workload> workloads = GetWorkloads();

    for (const models::Workload& workload : workloads)
    {
        if (workload.discipline_id == discipline_id)
        {
            return true;
        }
    }

    return false;
}
