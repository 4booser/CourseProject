#include "app/repositories/teacher.cpp"
#include <exception>
#include <iostream>
#include <cstdlib>
#include "ui.h"

int main()
{
#ifdef _WIN32
system("chcp 65001 > nul");
#endif

    //system("chcp 65001>nul");

    unsigned short choice;

    do{
        ui::ShowObjects();

        try{
            std::cin >> choice;

        }
        catch(std::exception exception){
            
        }
        

        switch(choice) {
            case 1:
                ui::ShowOptions();
                HandleTeacherCreate();
                break;
            case 2:

                break;
            case 3:

                break;
            case 4:

                break;
            case 5:

                break;
            default:
                std::cout << "Невірний пункт меню." << std::endl;
                break;
        }
    }
    while(choice != 0);

    return 0;
}