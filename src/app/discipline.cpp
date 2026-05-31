#include "repositories/discipline_repository.h"
#include "repositories/workload_repository.h"
#include "headers/discipline.h"
#include "ui/input.h"
#include "ui/table.h"
#include "models.h"
#include "common/operation_result.h"

#include <iostream>
#include <string>
#include <vector>
#include <optional>

void HandleDisciplineCreate()
{
    models::Discipline discipline{};

    ui::ClearInputLine();

    discipline.name = ui::ReadLine("Введiть назву дисциплiни: ");
    discipline.quota = ui::ReadUnsignedInt("Введiть кiлькiсть годин дисциплiни: ");

    OperationResult save_result = SaveDiscipline(discipline);
    if (!save_result.success)
    {
        std::cout << save_result.message << '\n';
        return;
    }

    std::cout << "Дисциплiну збережено.\n";
}

void HandleDisciplinesGet()
{
    std::vector<models::Discipline> disciplines = GetDisciplines();
    const std::vector<int> widths {5, 30, 10};

    ui::PrintRow(widths, "ID", "Name", "Hours");
    ui::PrintSeparator(45);

    for (const models::Discipline& discipline : disciplines)
    {
        ui::PrintRow(widths, discipline.id, discipline.name, discipline.quota);
    }
}

void HandleDisciplineEdit(const unsigned short& id)
{
    std::optional<models::Discipline> existing = GetDisciplineById(id);

    if (!existing.has_value())
    {
        std::cout << "Дисциплiну з таким Id не знайдено.\n";
        return;
    }

    models::Discipline discipline{};

    ui::ClearInputLine();

    discipline.name = ui::ReadLine("Введiть нову назву дисциплiни: ");
    discipline.quota = ui::ReadUnsignedInt("Введiть нову кiлькiсть годин дисциплiни: ");

    OperationResult edit_result = EditDisciplineById(id, discipline);
    if (!edit_result.success)
    {
        std::cout << edit_result.message << '\n';
        return;
    }

    std::cout << "Дисциплiну оновлено.\n";
}

void HandleDisciplineDelete(const unsigned short& id)
{
    if (HasWorkloadForDiscipline(id))
    {
        std::cout << "Операцiю заблоковано: дисциплiна використовується в навантаженнi.\n";
        return;
    }

    OperationResult remove_result = RemoveDisciplineById(id);
    if (!remove_result.success)
    {
        std::cout << remove_result.message << '\n';
        return;
    }

    std::cout << "Дисциплiну видалено.\n";
}
