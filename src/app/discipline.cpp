#include "repositories/discipline_repository.h"
#include "headers/discipline.h"
#include "services/discipline_service.h"
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

    OperationResult create_result = services::CreateDiscipline(discipline);
    if (!create_result.success)
    {
        std::cout << create_result.message << '\n';
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
    models::Discipline discipline{};

    ui::ClearInputLine();

    discipline.name = ui::ReadLine("Введiть нову назву дисциплiни: ");
    discipline.quota = ui::ReadUnsignedInt("Введiть нову кiлькiсть годин дисциплiни: ");

    OperationResult update_result = services::UpdateDiscipline(id, discipline);
    if (!update_result.success)
    {
        std::cout << update_result.message << '\n';
        return;
    }

    std::cout << "Дисциплiну оновлено.\n";
}

void HandleDisciplineDelete(const unsigned short& id)
{
    OperationResult delete_result = services::DeleteDiscipline(id);
    if (!delete_result.success)
    {
        std::cout << delete_result.message << '\n';
        return;
    }

    std::cout << "Дисциплiну видалено.\n";
}
