#include "repositories/teacher_repository.h"
#include "headers/teacher.h"
#include "models.h"
#include <iostream>


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