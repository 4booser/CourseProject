#include "repositories/group_repository.h"
#include "headers/group.h"
#include "models.h"
#include <iostream>
#include <iomanip>
#include <optional>
#include <limits>
#include <string>
#include <vector>

void HandleGroupCreate()
{
    models::Group group{};

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Введiть назву групи: ";
    std::getline(std::cin, group.name);

    std::cout << "Введiть курс: ";
    while (!(std::cin >> group.course))
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Помилка. Введiть число для курсу: ";
    }

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Введiть спецiальнiсть: ";
    std::getline(std::cin, group.speciality);

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

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Введiть нову назву групи: ";
    std::getline(std::cin, updated_group.name);

    std::cout << "Введiть новий курс: ";
    while (!(std::cin >> updated_group.course))
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Помилка. Введiть число для курсу: ";
    }

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Введiть нову спецiальнiсть: ";
    std::getline(std::cin, updated_group.speciality);

    if (!EditGroupById(id, updated_group))
    {
        std::cout << "Сталася помилка при редагуваннi групи.\n";
        return;
    }

    std::cout << "Групу оновлено.\n";
}

void HandleGroupDelete(const unsigned short& id)
{
    if (!DeleteGroupById(id))
    {
        std::cout << "Групу з таким Id не знайдено або сталася помилка.\n";
        return;
    }

    std::cout << "Групу видалено.\n";
}
