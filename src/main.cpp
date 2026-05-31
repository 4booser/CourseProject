#include "ui.h"
#include "ui/input.h"
#include "ui/menu_handlers.h"

#include <iostream>
#include <cstdlib>

int main()
{
#ifdef _WIN32
    system("chcp 65001 > nul");
#endif

    unsigned short object = 0;

    do{
        ui::ShowObjects();
        object = ui::ReadUnsignedShort("");

        switch(object) {
            case 1:
                ui::HandleTeacherMenu();
                break;
            case 2:
                ui::HandleDisciplineMenu();
                break;
            case 3:
                ui::HandleGroupMenu();
                break;
            case 4:
                ui::HandleWorkloadMenu();
                break;
            case 5:
                std::cout << "Пошук поки не реалiзовано.\n";
                break;
            case 0:
                std::cout << "Вихiд з програми." << std::endl;
                break;
            default:
                std::cout << "Невірний пункт меню." << std::endl;
                break;
        }
    }
    while(object != 0);

    return 0;
}
