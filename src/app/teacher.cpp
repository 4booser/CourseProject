#include "repositories/teacher_repository.h"
#include "headers/teacher.h"
#include "services/teacher_service.h"
#include "ui/input.h"
#include "ui/table.h"
#include "models.h"
#include "common/operation_result.h"
#include <string>
#include <iostream>
#include <optional>
#include <vector>

void HandleTeacherCreate(){
    models::Teacher teacher{};

    ui::ClearInputLine();

    teacher.full_name = ui::ReadLine("Введiть ПIБ: ");
    teacher.digital_commission = ui::ReadLine("Введiть цифрову комiсiю: ");
    teacher.quota = ui::ReadUnsignedInt("Введiть максимальну кiлькiсть годин: ");

    OperationResult create_result = services::CreateTeacher(teacher);
    if (!create_result.success)
    {
        std::cout << create_result.message << '\n';
        return;
    }

    std::cout << "\nВикладача збережено.\n";
}

void HandleTeachersPrint(){
    const std::vector<int> widths {5, 25, 20, 10};

    std::cout << std::endl;
    ui::PrintRow(widths, "ID", "Full name", "Commission", "Quota");
    ui::PrintSeparator(60);

    for (unsigned short i = 1; i <= GetLastTeacherId(); i++)
    {
        std::optional<models::Teacher> teacher = GetTeacherById(i);

        if (!teacher.has_value()) { continue; }

        ui::PrintRow(widths, teacher->id, teacher->full_name, teacher->digital_commission, teacher->quota);
    }
}

void HandleTeacherEdit(const unsigned short& id)
{
    models::Teacher updated_teacher{};

    ui::ClearInputLine();

    updated_teacher.full_name = ui::ReadLine("Введiть нове ПIБ: ");
    updated_teacher.digital_commission = ui::ReadLine("Введiть нову цифрову комiсiю: ");
    updated_teacher.quota = ui::ReadUnsignedInt("Введiть нову максимальну кiлькiсть годин: ");

    OperationResult update_result = services::UpdateTeacher(id, updated_teacher);
    if (!update_result.success)
    {
        std::cout << update_result.message << '\n';
        return;
    }

    std::cout << "Викладача оновлено.\n";
}

void HandleTeacherDelete(const unsigned short& id)
{
    OperationResult result = services::DeleteTeacher(id);
    if (!result.success)
    {
        std::cout << result.message << '\n';
        return;
    }

    std::cout << "Викладача видалено.\n";
}
