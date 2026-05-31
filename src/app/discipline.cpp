#include "repositories/discipline_repository.h"
#include "headers/discipline.h"
#include "models.h"

#include <iostream>
#include <iomanip>
#include <limits>
#include <string>
#include <vector>
#include <optional>

void HandleDisciplineCreate()
{
    models::Discipline discipline{};

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Name: ";
    std::getline(std::cin, discipline.name);

    std::cout << "Hours: ";
    std::cin >> discipline.quota;

    if (!SaveDiscipline(discipline))
    {
        std::cout << "Save error.\n";
        return;
    }

    std::cout << "Saved.\n";
}

void HandleDisciplinesGet()
{
    std::vector<models::Discipline> disciplines = GetDisciplines();

    std::cout << std::left
        << std::setw(5) << "ID"
        << std::setw(30) << "Name"
        << std::setw(10) << "Hours"
        << std::endl;

    std::cout << std::string(45, '-') << std::endl;

    for (const models::Discipline& discipline : disciplines)
    {
        std::cout << std::left
            << std::setw(5) << discipline.id
            << std::setw(30) << discipline.name
            << std::setw(10) << discipline.quota
            << std::endl;
    }
}

void HandleDisciplineEdit(const unsigned short& id)
{
    std::optional<models::Discipline> existing = GetDisciplineById(id);

    if (!existing.has_value())
    {
        std::cout << "Not found.\n";
        return;
    }

    models::Discipline discipline{};

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "New name: ";
    std::getline(std::cin, discipline.name);

    std::cout << "New hours: ";
    std::cin >> discipline.quota;

    if (!EditDisciplineById(id, discipline))
    {
        std::cout << "Edit error.\n";
        return;
    }

    std::cout << "Updated.\n";
}

void HandleDisciplineDelete(const unsigned short& id)
{
    if (!RemoveDisciplineById(id))
    {
        std::cout << "Not found.\n";
        return;
    }

    std::cout << "Removed.\n";
}
