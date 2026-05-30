#include "repositories/teacher_repository.h"
#include "headers/teacher.h"
#include "models.h"
#include <iostream>


void HandleTeacherCreate(){
    models::Teacher teacher{};

    std::cout << "\nВведiть ID викладача: ";
    while (!(std::cin >> teacher.Id))
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Помилка. Введiть число для ID: ";
    }

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Введiть ПIБ: ";
    std::getline(std::cin, teacher.FullName);

    std::cout << "Введiть цифрову комiсiю: ";
    std::getline(std::cin, teacher.DigitalCommission);

    std::cout << "Введiть максимальну кiлькiсть годин: ";
    while (!(std::cin >> teacher.Quota))
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Помилка. Введiть число для годин: ";
    }

    SaveTeacher(teacher);

    std::cout << "\nВикладача збережено.\n";
}