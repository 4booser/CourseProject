#include "services/workload_service.h"

#include "repositories/teacher_repository.h"
#include "repositories/group_repository.h"
#include "repositories/discipline_repository.h"
#include "repositories/workload_repository.h"

#include <algorithm>
#include <optional>
#include <set>
#include <string>
#include <vector>

namespace
{
    constexpr unsigned int MaxWorkloadHours = 1000;

    bool ContainsId(const std::vector<unsigned short>& ids, unsigned short id)
    {
        return std::find(ids.begin(), ids.end(), id) != ids.end();
    }

    bool HasDuplicates(const std::vector<unsigned short>& ids)
    {
        std::set<unsigned short> unique_ids;

        for (unsigned short id : ids)
        {
            if (!unique_ids.insert(id).second)
            {
                return true;
            }
        }

        return false;
    }

    unsigned int GetTeacherAssignedHours(
        const std::vector<models::Workload>& workloads,
        unsigned short teacher_id,
        unsigned short excluded_workload_id)
    {
        unsigned int total = 0;

        for (const models::Workload& workload : workloads)
        {
            if (workload.id == excluded_workload_id)
            {
                continue;
            }

            if (ContainsId(workload.teacher_ids, teacher_id))
            {
                total += workload.total_hours;
            }
        }

        return total;
    }

    unsigned int GetDisciplineAssignedHours(
        const std::vector<models::Workload>& workloads,
        unsigned short discipline_id,
        unsigned short excluded_workload_id)
    {
        unsigned int total = 0;

        for (const models::Workload& workload : workloads)
        {
            if (workload.id == excluded_workload_id)
            {
                continue;
            }

            if (workload.discipline_id == discipline_id)
            {
                total += workload.total_hours;
            }
        }

        return total;
    }

    OperationResult ValidateTeacherIds(const std::vector<unsigned short>& teacher_ids)
    {
        if (teacher_ids.empty())
        {
            return OperationResult::Fail("Потрiбно вказати хоча б одного викладача.");
        }

        if (HasDuplicates(teacher_ids))
        {
            return OperationResult::Fail("Список викладачiв не може мiстити дублiкати Id.");
        }

        for (unsigned short teacher_id : teacher_ids)
        {
            if (!GetTeacherById(teacher_id).has_value())
            {
                return OperationResult::Fail("Викладача з Id " + std::to_string(teacher_id) + " не iснує.");
            }
        }

        return OperationResult::Ok();
    }

    OperationResult ValidateGroupIds(const std::vector<unsigned short>& group_ids)
    {
        if (group_ids.empty())
        {
            return OperationResult::Fail("Потрiбно вказати хоча б одну групу.");
        }

        if (HasDuplicates(group_ids))
        {
            return OperationResult::Fail("Список груп не може мiстити дублiкати Id.");
        }

        for (unsigned short group_id : group_ids)
        {
            if (!GetGroupById(group_id).has_value())
            {
                return OperationResult::Fail("Групи з Id " + std::to_string(group_id) + " не iснує.");
            }
        }

        return OperationResult::Ok();
    }

    OperationResult ValidateDisciplineId(unsigned short discipline_id)
    {
        if (!GetDisciplineById(discipline_id).has_value())
        {
            return OperationResult::Fail("Дисциплiни з Id " + std::to_string(discipline_id) + " не iснує.");
        }

        return OperationResult::Ok();
    }

    OperationResult ValidateHoursRange(const models::Workload& workload)
    {
        if (workload.total_hours == 0)
        {
            return OperationResult::Fail("Кiлькiсть годин навантаження не може бути 0.");
        }

        if (workload.total_hours > MaxWorkloadHours)
        {
            return OperationResult::Fail("Кiлькiсть годин навантаження занадто велика.");
        }

        return OperationResult::Ok();
    }

    OperationResult ValidateTeacherQuotas(
        const std::vector<models::Workload>& workloads,
        const models::Workload& workload,
        unsigned short excluded_workload_id)
    {
        for (unsigned short teacher_id : workload.teacher_ids)
        {
            std::optional<models::Teacher> teacher = GetTeacherById(teacher_id);

            if (!teacher.has_value())
            {
                return OperationResult::Fail("Викладача з Id " + std::to_string(teacher_id) + " не iснує.");
            }

            unsigned int assigned_hours = GetTeacherAssignedHours(workloads, teacher_id, excluded_workload_id);
            unsigned int new_total = assigned_hours + workload.total_hours;

            if (new_total > teacher->quota)
            {
                return OperationResult::Fail(
                    "Навантаження викладача з Id " + std::to_string(teacher_id) +
                    " перевищує квоту. Поточнi години: " + std::to_string(assigned_hours) +
                    ", нове навантаження: " + std::to_string(workload.total_hours) +
                    ", квота: " + std::to_string(teacher->quota) + ".");
            }
        }

        return OperationResult::Ok();
    }

    OperationResult ValidateDisciplineQuota(
        const std::vector<models::Workload>& workloads,
        const models::Workload& workload,
        unsigned short excluded_workload_id)
    {
        std::optional<models::Discipline> discipline = GetDisciplineById(workload.discipline_id);

        if (!discipline.has_value())
        {
            return OperationResult::Fail("Дисциплiни з Id " + std::to_string(workload.discipline_id) + " не iснує.");
        }

        unsigned int assigned_hours = GetDisciplineAssignedHours(workloads, workload.discipline_id, excluded_workload_id);
        unsigned int new_total = assigned_hours + workload.total_hours;

        if (new_total > discipline->quota)
        {
            return OperationResult::Fail(
                "Навантаження дисциплiни з Id " + std::to_string(workload.discipline_id) +
                " перевищує кiлькiсть годин дисциплiни. Поточнi години: " + std::to_string(assigned_hours) +
                ", нове навантаження: " + std::to_string(workload.total_hours) +
                ", лiмiт: " + std::to_string(discipline->quota) + ".");
        }

        return OperationResult::Ok();
    }
}

namespace services
{
    OperationResult ValidateWorkload(const models::Workload& workload, unsigned short excluded_workload_id)
    {
        std::vector<models::Workload> workloads = GetWorkloads();

        OperationResult result = ValidateTeacherIds(workload.teacher_ids);
        if (!result.success) { return result; }

        result = ValidateGroupIds(workload.group_ids);
        if (!result.success) { return result; }

        result = ValidateDisciplineId(workload.discipline_id);
        if (!result.success) { return result; }

        result = ValidateHoursRange(workload);
        if (!result.success) { return result; }

        result = ValidateTeacherQuotas(workloads, workload, excluded_workload_id);
        if (!result.success) { return result; }

        return ValidateDisciplineQuota(workloads, workload, excluded_workload_id);
    }

    OperationResult CreateWorkload(models::Workload& workload)
    {
        OperationResult validation_result = ValidateWorkload(workload);
        if (!validation_result.success)
        {
            return validation_result;
        }

        return SaveWorkload(workload);
    }

    OperationResult UpdateWorkload(unsigned short workload_id, const models::Workload& workload)
    {
        if (!GetWorkloadById(workload_id).has_value())
        {
            return OperationResult::Fail("Навантаження з таким Id не знайдено.");
        }

        OperationResult validation_result = ValidateWorkload(workload, workload_id);
        if (!validation_result.success)
        {
            return validation_result;
        }

        return EditWorkloadById(workload_id, workload);
    }

    OperationResult DeleteWorkload(unsigned short workload_id)
    {
        return RemoveWorkloadById(workload_id);
    }
}
