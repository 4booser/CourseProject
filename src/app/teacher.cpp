#include "repositories/teacher_repository.h"
#include "repositories/workload_repository.h"
#include "headers/teacher.h"
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

    OperationResult save_result = SaveTeacher(teacher);
    if(!save_result.success){
        std::cout << save_result.message << '\n';
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
    std::optional<models::Teacher> existing_teacher = GetTeacherById(id);

    if (!existing_teacher.has_value())
    {
        std::cout << "Викладача з таким Id не знайдено.\n";
        return;
    }

    models::Teacher updated_teacher{};

    ui::ClearInputLine();

    updated_teacher.full_name = ui::ReadLine("Введiть нове ПIБ: ");
    updated_teacher.digital_commission = ui::ReadLine("Введiть нову цифрову комiсiю: ");
    updated_teacher.quota = ui::ReadUnsignedInt("Введiть нову максимальну кiлькiсть годин: ");

    OperationResult edit_result = EditTeacherById(id, updated_teacher);
    if (!edit_result.success)
    {
        std::cout << edit_result.message << '\n';
        return;
    }

    std::cout << "Викладача оновлено.\n";
}

void HandleTeacherDelete(const unsigned short& id)
{
    if (HasWorkloadForTeacher(id))
    {
        std::cout << "Неможливо видалити викладача: вiн використовується в навантаженнi.\n";
        return;
    }

    OperationResult delete_result = DeleteTeacherById(id);
    if (!delete_result.success)
    {
        std::cout << delete_result.message << '\n';
        return;
    }

    std::cout << "Викладача видалено.\n";
}
