#include "repositories/discipline_repository.h"
#include "repositories/workload_repository.h"
#include "headers/discipline.h"
#include "models.h"

#include <iostream>
#include <iomanip>
#include <limits>
#include <string>
#include <vector>
#include <optional>

static unsigned int ReadUnsignedInt(const std::string& prompt)
{
    unsigned int value = 0;

    std::cout << prompt;

    while (!(std::cin >> value))
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Помилка. Введiть число: ";
    }

    return value;
}

void HandleDisciplineCreate()
{
    models::Discipline discipline{};

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Введiть назву дисциплiни: ";
    std::getline(std::cin, discipline.name);

    discipline.quota = ReadUnsignedInt("Введiть кiлькiсть годин дисциплiни: ");

    if (!SaveDiscipline(discipline))
    {
        std::cout << "Сталася помилка при збереженнi дисциплiни.\n";
        return;
    }

    std::cout << "Дисциплiну збережено.\n";
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
        std::cout << "Дисциплiну з таким Id не знайдено.\n";
        return;
    }

    models::Discipline discipline{};

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Введiть нову назву дисциплiни: ";
    std::getline(std::cin, discipline.name);

    discipline.quota = ReadUnsignedInt("Введiть нову кiлькiсть годин дисциплiни: ");

    if (!EditDisciplineById(id, discipline))
    {
        std::cout << "Сталася помилка при редагуваннi дисциплiни.\n";
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

    if (!RemoveDisciplineById(id))
    {
        std::cout << "Дисциплiну з таким Id не знайдено.\n";
        return;
    }

    std::cout << "Дисциплiну видалено.\n";
}
