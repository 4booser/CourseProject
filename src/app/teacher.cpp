#include "repositories/teacher_repository.h"
#include "repositories/workload_repository.h"
#include "headers/teacher.h"
#include "models.h"
#include <string>
#include <iostream>
#include <optional>
#include <iomanip>
#include <limits>

void HandleTeacherCreate(){
    models::Teacher teacher{};

    std::cin.ignore();

    std::cout << "Введiть ПIБ: ";
    std::getline(std::cin, teacher.full_name);

    std::cout << "Введiть цифрову комiсiю: ";
    std::getline(std::cin, teacher.digital_commission);

    std::cout << "Введiть максимальну кiлькiсть годин: ";
    while (!(std::cin >> teacher.quota))
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Помилка. Введiть число для годин: ";
    }

    if(!SaveTeacher(teacher)){
        std:: cout << "Сталася помилка при збереженнi.";
        return;
    }

    std::cout << "\nВикладача збережено.\n";
}

void HandleTeachersPrint(){
    std::cout << std::endl;
    std::cout << std::left
        << std::setw(5)  << "ID"
        << std::setw(25) << "Full name"
        << std::setw(20) << "Commission"
        << std::setw(10) << "Quota"
        << std::endl;
    std::cout << std::string(60, '-') << std::endl;

    for (unsigned short i = 1; i <= GetLastTeacherId(); i++)
    {
        std::optional<models::Teacher> teacher = GetTeacherById(i);

        if (!teacher.has_value()) { continue; }

        std::cout << std::left
            << std::setw(5) << teacher->id
            << std::setw(25) << teacher->full_name
            << std::setw(20) << teacher->digital_commission
            << std::setw(10) << teacher->quota
            << std::endl;
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

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Введiть нове ПIБ: ";
    std::getline(std::cin, updated_teacher.full_name);

    std::cout << "Введiть нову цифрову комiсiю: ";
    std::getline(std::cin, updated_teacher.digital_commission);

    std::cout << "Введiть нову максимальну кiлькiсть годин: ";
    while (!(std::cin >> updated_teacher.quota))
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Помилка. Введiть число для годин: ";
    }

    if (!EditTeacherById(id, updated_teacher))
    {
        std::cout << "Сталася помилка при редагуваннi викладача.\n";
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

    if (!DeleteTeacherById(id))
    {
        std::cout << "Викладача з таким Id не знайдено або сталася помилка.\n";
        return;
    }

    std::cout << "Викладача видалено.\n";
}
