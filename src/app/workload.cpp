#include "repositories/workload_repository.h"
#include "repositories/teacher_repository.h"
#include "repositories/group_repository.h"
#include "repositories/discipline_repository.h"
#include "headers/workload.h"
#include "ui/input.h"
#include "models.h"

#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <limits>
#include <optional>

static bool AreTeacherIdsValid(const std::vector<unsigned short>& teacher_ids)
{
    if (teacher_ids.empty())
    {
        std::cout << "Потрiбно вказати хоча б одного викладача.\n";
        return false;
    }

    for (unsigned short teacher_id : teacher_ids)
    {
        if (!GetTeacherById(teacher_id).has_value())
        {
            std::cout << "Викладача з Id " << teacher_id << " не iснує.\n";
            return false;
        }
    }

    return true;
}

static bool AreGroupIdsValid(const std::vector<unsigned short>& group_ids)
{
    if (group_ids.empty())
    {
        std::cout << "Потрiбно вказати хоча б одну групу.\n";
        return false;
    }

    for (unsigned short group_id : group_ids)
    {
        if (!GetGroupById(group_id).has_value())
        {
            std::cout << "Групи з Id " << group_id << " не iснує.\n";
            return false;
        }
    }

    return true;
}

static bool IsDisciplineIdValid(unsigned short discipline_id)
{
    if (!GetDisciplineById(discipline_id).has_value())
    {
        std::cout << "Дисциплiни з Id " << discipline_id << " не iснує.\n";
        return false;
    }

    return true;
}

static bool IsWorkloadValid(const models::Workload& workload)
{
    return
        AreTeacherIdsValid(workload.teacher_ids) &&
        AreGroupIdsValid(workload.group_ids) &&
        IsDisciplineIdValid(workload.discipline_id);
}

static void ReadWorkloadFields(models::Workload& workload)
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    workload.teacher_ids = ui::ReadUnsignedShortList("Введiть Id викладачiв через пробiл: ");
    workload.group_ids = ui::ReadUnsignedShortList("Введiть Id груп через пробiл: ");
    workload.discipline_id = ui::ReadUnsignedShort("Введiть Id дисциплiни: ");
    workload.lectures = ui::ReadUnsignedInt("Введiть кiлькiсть лекцiйних годин: ");
    workload.practical_classes = ui::ReadUnsignedInt("Введiть кiлькiсть практичних годин: ");
    workload.laboratory_classes = ui::ReadUnsignedInt("Введiть кiлькiсть лабораторних годин: ");
    workload.seminars = ui::ReadUnsignedInt("Введiть кiлькiсть семiнарських годин: ");
    workload.consultations = ui::ReadUnsignedInt("Введiть кiлькiсть годин консультацiй: ");

    workload.total_hours =
        workload.lectures +
        workload.practical_classes +
        workload.laboratory_classes +
        workload.seminars +
        workload.consultations;
}

void HandleWorkloadCreate()
{
    models::Workload workload{};

    ReadWorkloadFields(workload);

    if (!IsWorkloadValid(workload))
    {
        std::cout << "Навантаження не збережено.\n";
        return;
    }

    if (!SaveWorkload(workload))
    {
        std::cout << "Сталася помилка при збереженнi навантаження.\n";
        return;
    }

    std::cout << "Навантаження збережено.\n";
}

void HandleWorkloadsGet()
{
    std::vector<models::Workload> workloads = GetWorkloads();

    std::cout << std::endl;
    std::cout << std::left
        << std::setw(5)  << "ID"
        << std::setw(15) << "Teachers"
        << std::setw(15) << "Groups"
        << std::setw(12) << "Disc ID"
        << std::setw(10) << "Lect"
        << std::setw(10) << "Pract"
        << std::setw(10) << "Lab"
        << std::setw(10) << "Sem"
        << std::setw(10) << "Cons"
        << std::setw(10) << "Total"
        << std::endl;

    std::cout << std::string(107, '-') << std::endl;

    for (const models::Workload& workload : workloads)
    {
        std::cout << std::left << std::setw(5) << workload.id;

        std::ostringstream teachers_stream;
        for (std::size_t i = 0; i < workload.teacher_ids.size(); ++i)
        {
            teachers_stream << workload.teacher_ids[i];
            if (i + 1 < workload.teacher_ids.size())
            {
                teachers_stream << ",";
            }
        }

        std::ostringstream groups_stream;
        for (std::size_t i = 0; i < workload.group_ids.size(); ++i)
        {
            groups_stream << workload.group_ids[i];
            if (i + 1 < workload.group_ids.size())
            {
                groups_stream << ",";
            }
        }

        std::cout
            << std::setw(15) << teachers_stream.str()
            << std::setw(15) << groups_stream.str()
            << std::setw(12) << workload.discipline_id
            << std::setw(10) << workload.lectures
            << std::setw(10) << workload.practical_classes
            << std::setw(10) << workload.laboratory_classes
            << std::setw(10) << workload.seminars
            << std::setw(10) << workload.consultations
            << std::setw(10) << workload.total_hours
            << std::endl;
    }
}

void HandleWorkloadEdit(const unsigned short& id)
{
    std::optional<models::Workload> existing_workload = GetWorkloadById(id);

    if (!existing_workload.has_value())
    {
        std::cout << "Навантаження не знайдено.\n";
        return;
    }

    models::Workload updated_workload{};
    ReadWorkloadFields(updated_workload);

    if (!IsWorkloadValid(updated_workload))
    {
        std::cout << "Навантаження не оновлено.\n";
        return;
    }

    if (!EditWorkloadById(id, updated_workload))
    {
        std::cout << "Сталася помилка при редагуваннi навантаження.\n";
        return;
    }

    std::cout << "Навантаження оновлено.\n";
}

void HandleWorkloadDelete(const unsigned short& id)
{
    if (!RemoveWorkloadById(id))
    {
        std::cout << "Навантаження не знайдено.\n";
        return;
    }

    std::cout << "Навантаження видалено.\n";
}
