#include "repositories/workload_repository.h"
#include "headers/workload.h"
#include "services/workload_service.h"
#include "common/operation_result.h"
#include "ui/input.h"
#include "ui/table.h"
#include "models.h"

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <optional>

static std::string JoinIds(const std::vector<unsigned short>& ids)
{
    std::ostringstream stream;

    for (std::size_t i = 0; i < ids.size(); ++i)
    {
        stream << ids[i];

        if (i + 1 < ids.size())
        {
            stream << ",";
        }
    }

    return stream.str();
}

static void ReadWorkloadFields(models::Workload& workload)
{
    ui::ClearInputLine();

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

    OperationResult validation_result = services::ValidateWorkload(workload);
    if (!validation_result.success)
    {
        std::cout << validation_result.message << '\n';
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
    const std::vector<int> widths {5, 15, 15, 12, 10, 10, 10, 10, 10, 10};

    std::cout << std::endl;
    ui::PrintRow(widths, "ID", "Teachers", "Groups", "Disc ID", "Lect", "Pract", "Lab", "Sem", "Cons", "Total");
    ui::PrintSeparator(107);

    for (const models::Workload& workload : workloads)
    {
        ui::PrintRow(widths,
            workload.id,
            JoinIds(workload.teacher_ids),
            JoinIds(workload.group_ids),
            workload.discipline_id,
            workload.lectures,
            workload.practical_classes,
            workload.laboratory_classes,
            workload.seminars,
            workload.consultations,
            workload.total_hours);
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

    OperationResult validation_result = services::ValidateWorkload(updated_workload, id);
    if (!validation_result.success)
    {
        std::cout << validation_result.message << '\n';
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
