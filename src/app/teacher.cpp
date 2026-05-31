#include "repositories/teacher_repository.h"
#include "headers/teacher.h"
#include "models.h"
#include <string>
#include <iostream>
#include <optional>
#include <iomanip>


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
    }

    std::cout << "\nВикладача збережено.\n";
}

void HandleTeachersPrint(){
    std::cout << std::endl;
    std::cout << std::left
        << std::setw(5)  << "ID"
        << std::setw(20) << "Full name"
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