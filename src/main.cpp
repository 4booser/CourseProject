#include <iostream>
#include <cstdlib>

extern void ShowObjects();

int main()
{
    system("chcp 65001>nul");

    ushort choice;

    do{
        ShowObjects();

        std::cin >> choice

        switch(choice) {
            case 1:

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