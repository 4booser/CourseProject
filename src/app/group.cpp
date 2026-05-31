#include "repositories/group_repository.h"
#include "repositories/workload_repository.h"
#include "headers/group.h"
#include "ui/input.h"
#include "models.h"
#include <iostream>
#include <iomanip>
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

    if (!SaveGroup(group))
    {
        std::cout << "Сталася помилка при збереженнi групи.\n";
        return;
    }

    std::cout << "\nГрупу збережено.\n";
}

void HandleGroupsGet()
{
    std::vector<models::Group> groups = GetGroups();

    std::cout << std::endl;
    std::cout << std::left
        << std::setw(5)  << "ID"
        << std::setw(15) << "Name"
        << std::setw(10) << "Course"
        << std::setw(25) << "Speciality"
        << std::endl;
    std::cout << std::string(55, '-') << std::endl;

    for (const models::Group& group : groups)
    {
        std::cout << std::left
            << std::setw(5)  << group.id
            << std::setw(15) << group.name
            << std::setw(10) << group.course
            << std::setw(25) << group.speciality
            << std::endl;
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

    if (!EditGroupById(id, updated_group))
    {
        std::cout << "Сталася помилка при редагуваннi групи.\n";
        return;
    }

    std::cout << "Групу оновлено.\n";
}

void HandleGroupDelete(const unsigned short& id)
{
    if (HasWorkloadForGroup(id))
    {
        std::cout << "Неможливо видалити групу: вона використовується в навантаженнi.\n";
        return;
    }

    if (!DeleteGroupById(id))
    {
        std::cout << "Групу з таким Id не знайдено або сталася помилка.\n";
        return;
    }

    std::cout << "Групу видалено.\n";
}
