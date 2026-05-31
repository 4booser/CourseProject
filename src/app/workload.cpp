#include "repositories/workload_repository.h"
#include "headers/workload.h"
#include "services/workload_service.h"
#include "common/operation_result.h"
#include "ui/input.h"
#include "ui/table.h"
#include "utils/string_utils.h"
#include "models.h"

#include <iostream>
#include <string>
#include <vector>

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

    OperationResult create_result = services::CreateWorkload(workload);
    if (!create_result.success)
    {
        std::cout << create_result.message << '\n';
        std::cout << "Навантаження не збережено.\n";
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
            utils::JoinIds(workload.teacher_ids),
            utils::JoinIds(workload.group_ids),
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
    models::Workload updated_workload{};
    ReadWorkloadFields(updated_workload);

    OperationResult update_result = services::UpdateWorkload(id, updated_workload);
    if (!update_result.success)
    {
        std::cout << update_result.message << '\n';
        std::cout << "Навантаження не оновлено.\n";
        return;
    }

    std::cout << "Навантаження оновлено.\n";
}

void HandleWorkloadDelete(const unsigned short& id)
{
    OperationResult delete_result = services::DeleteWorkload(id);
    if (!delete_result.success)
    {
        std::cout << delete_result.message << '\n';
        return;
    }

    std::cout << "Навантаження видалено.\n";
}
