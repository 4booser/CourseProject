#include "headers/teacher.h"
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

    unsigned short object;
    unsigned short option;

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
                }
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
    while(object != 0);

    return 0;
}