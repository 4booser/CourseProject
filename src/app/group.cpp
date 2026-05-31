#include "repositories/group_repository.h"
#include "headers/group.h"
#include "services/group_service.h"
#include "ui/input.h"
#include "ui/table.h"
#include "models.h"
#include "common/operation_result.h"
#include <iostream>
#include <optional>
#include <string>
#include <vector>

void HandleGroupCreate()
{
    models::Group group{};

    ui::ClearInputLine();

    group.name = ui::ReadLine("Введiть назву групи: ");
    group.course = ui::ReadUnsignedShort("Введiть курс: ");
    ui::ClearInputLine();
    group.speciality = ui::ReadLine("Введiть спецiальнiсть: ");

    OperationResult validation_result = services::ValidateGroup(group);
    if (!validation_result.success)
    {
        std::cout << validation_result.message << '\n';
        return;
    }

    OperationResult save_result = SaveGroup(group);
    if (!save_result.success)
    {
        std::cout << save_result.message << '\n';
        return;
    }

    std::cout << "\nГрупу збережено.\n";
}

void HandleGroupsGet()
{
    std::vector<models::Group> groups = GetGroups();
    const std::vector<int> widths {5, 15, 10, 25};

    std::cout << std::endl;
    ui::PrintRow(widths, "ID", "Name", "Course", "Speciality");
    ui::PrintSeparator(55);

    for (const models::Group& group : groups)
    {
        ui::PrintRow(widths, group.id, group.name, group.course, group.speciality);
    }
}

void HandleGroupEdit(const unsigned short& id)
{
    std::optional<models::Group> existing_group = GetGroupById(id);

    if (!existing_group.has_value())
    {
        std::cout << "Групу з таким Id не знайдено.\n";
        return;
    }

    models::Group updated_group{};

    ui::ClearInputLine();

    updated_group.name = ui::ReadLine("Введiть нову назву групи: ");
    updated_group.course = ui::ReadUnsignedShort("Введiть новий курс: ");
    ui::ClearInputLine();
    updated_group.speciality = ui::ReadLine("Введiть нову спецiальнiсть: ");

    OperationResult validation_result = services::ValidateGroup(updated_group);
    if (!validation_result.success)
    {
        std::cout << validation_result.message << '\n';
        return;
    }

    OperationResult edit_result = EditGroupById(id, updated_group);
    if (!edit_result.success)
    {
        std::cout << edit_result.message << '\n';
        return;
    }

    std::cout << "Групу оновлено.\n";
}

void HandleGroupDelete(const unsigned short& id)
{
    OperationResult can_delete_result = services::CanDeleteGroup(id);
    if (!can_delete_result.success)
    {
        std::cout << can_delete_result.message << '\n';
        return;
    }

    OperationResult delete_result = DeleteGroupById(id);
    if (!delete_result.success)
    {
        std::cout << delete_result.message << '\n';
        return;
    }

    std::cout << "Групу видалено.\n";
}
