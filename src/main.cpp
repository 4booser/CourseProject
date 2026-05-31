#include "headers/teacher.h"
#include "headers/workload.h"
#include "headers/discipline.h"
#include "headers/subject.h"
#include "headers/group.h"
#include "ui.h"
#include <exception>
#include <iostream>
#include <cstdlib>

int main()
{
#ifdef _WIN32
system("chcp 65001 > nul");
#endif

    //system("chcp 65001>nul");

    unsigned short object, option, id;

    do{
        ui::ShowObjects();

        try{
            std::cin >> object;
        }
        catch(const std::exception& exception){
            
        }
        

        switch(object) {
            case 1:
                ui::ShowOptions();
                std::cin >> option;
                
                switch(option){
                    case 1:
                    HandleTeacherCreate();
                        break;
                    case 2:
                    HandleTeachersPrint();
                        break;
                    case 3:
                    HandleTeachersPrint();
                    std::cout << "Введiть Id викладача для редагування: ";
                    std::cin >> id;
                    HandleTeacherEdit(id);
                        break;
                    case 4:
                    std::cout << "Введiть Id викладача для видалення: ";
                    HandleTeachersPrint();
                    std::cin >> id;
                    HandleTeacherDelete(id);
                        break;
                }
                break;
            case 2:
                ui::ShowOptions();
                std::cin >> option;

                switch(option){
                    case 1:
                    HandleDisciplineCreate();
                        break;
                    case 2:
                    HandleDisciplinesGet();
                        break;
                    case 3:
                    HandleDisciplinesGet();
                    std::cout << "Введiть Id дисциплiни для редагування: ";
                    std::cin >> id;
                    HandleDisciplineEdit(id);
                        break;
                    case 4:
                    HandleDisciplinesGet();
                    std::cout << "Введiть Id дисциплiни для видалення: ";
                    std::cin >> id;
                    HandleDisciplineDelete(id);
                        break;
                }
                break;
            case 3:
                ui::ShowOptions();
                std::cin >> option;

                switch(option){
                    case 1:
                    HandleGroupCreate();
                        break;
                    case 2:
                    HandleGroupsGet();
                        break;
                    case 3:
                    HandleGroupsGet();
                    std::cout << "Введiть Id групи для редагування: ";
                    std::cin >> id;
                    HandleGroupEdit(id);
                        break;
                    case 4:
                    HandleGroupsGet();
                    std::cout << "Введiть Id групи для видалення: ";
                    std::cin >> id;
                    HandleGroupDelete(id);
                        break;
                }
                break;
            case 4:
                ui::ShowOptions();
                std::cin >> option;

                switch(option){
                    case 1:
                    HandleWorkloadCreate();
                        break;
                    case 2:
                    HandleWorkloadsGet();
                        break;
                    case 3:
                    HandleWorkloadsGet();
                    std::cout << "Введiть Id навантаження для редагування: ";
                    std::cin >> id;
                    HandleWorkloadEdit(id);
                        break;
                    case 4:
                    HandleWorkloadsGet();
                    std::cout << "Введiть Id навантаження для видалення: ";
                    std::cin >> id;
                    HandleWorkloadDelete(id);
                        break;
                }
                break;
            case 5:

                break;
            case 0:
                std::cout << "Вихiд з програми." << std::endl;;
                break;
            default:
                std::cout << "Невірний пункт меню." << std::endl;
                break;
        }
    }
    while(object != 0);

    return 0;
}
