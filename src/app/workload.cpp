#include "repositories/workload_repository.h"
#include "headers/workload.h"
#include "models.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <limits>

static std::vector<unsigned short> ReadIdsFromLine()
{
    std::vector<unsigned short> ids;
    std::string line;

    std::getline(std::cin, line);

    std::istringstream stream(line);
    unsigned short id;

    while (stream >> id)
    {
        ids.push_back(id);
    }

    return ids;
}

void HandleWorkloadCreate(){
    models::Workload workload{};

    std::cin.ignore();
    
    std::cout << "Оберiть вiдповiдальних за навантаження викладачiв за Id: ";
    workload.teacher_ids = ReadIdsFromLine();

    std::cout << "\nОберiть групи якi вiдносяться до навантаження за Id: ";
    workload.group_ids = ReadIdsFromLine();

    std::cout << "\nВкажiть Id предмету: ";
    std::cin >> workload.subject_id;

    std::cout << "\nВкажiть кiлькiсть годин лекцiйних занять: ";
    std::cin >> workload.lectures;

    std::cout << "\nВкажiть кiлькiсть годин практичних занять: ";
    std::cin >> workload.practical_classes;

    std::cout << "\nВкажiть кiлькiсть годин лабораторних занять: ";
    std::cin >> workload.laboratory_classes;

    std::cout << "\nВкажiть кiлькiсть годин семiнарських занять: ";
    std::cin >> workload.seminars;

    std::cout << "\nВкажiть кiлькiсть годин консультацiй: ";
    std::cin >> workload.consultations;

    std::cout << std::endl;

    workload.total_hours =
        workload.lectures +
        workload.practical_classes +
        workload.laboratory_classes +
        workload.seminars +
        workload.consultations;

    if(!SaveWorkload(workload)){
        std::cout << "Сталася помилка при збереженнi.";
        return;
    }
    std::cout << "\nНавантаження збережено.\n";
}