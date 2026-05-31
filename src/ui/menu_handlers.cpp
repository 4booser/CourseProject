#include "ui/menu_handlers.h"

#include "headers/teacher.h"
#include "headers/workload.h"
#include "headers/discipline.h"
#include "headers/group.h"
#include "ui.h"
#include "ui/input.h"

#include <iostream>

namespace ui
{
    void HandleTeacherMenu()
    {
        ShowOptions();
        unsigned short option = ReadUnsignedShort("");

        switch(option){
            case 1:
                HandleTeacherCreate();
                break;
            case 2:
                HandleTeachersPrint();
                break;
            case 3:
                HandleTeachersPrint();
                HandleTeacherEdit(ReadUnsignedShort("Введiть Id викладача для редагування: "));
                break;
            case 4:
                HandleTeachersPrint();
                HandleTeacherDelete(ReadUnsignedShort("Введiть Id викладача для видалення: "));
                break;
            case 0:
                break;
            default:
                std::cout << "Невiрна опцiя.\n";
                break;
        }
    }

    void HandleDisciplineMenu()
    {
        ShowOptions();
        unsigned short option = ReadUnsignedShort("");

        switch(option){
            case 1:
                HandleDisciplineCreate();
                break;
            case 2:
                HandleDisciplinesGet();
                break;
            case 3:
                HandleDisciplinesGet();
                HandleDisciplineEdit(ReadUnsignedShort("Введiть Id дисциплiни для редагування: "));
                break;
            case 4:
                HandleDisciplinesGet();
                HandleDisciplineDelete(ReadUnsignedShort("Введiть Id дисциплiни для видалення: "));
                break;
            case 0:
                break;
            default:
                std::cout << "Невiрна опцiя.\n";
                break;
        }
    }

    void HandleGroupMenu()
    {
        ShowOptions();
        unsigned short option = ReadUnsignedShort("");

        switch(option){
            case 1:
                HandleGroupCreate();
                break;
            case 2:
                HandleGroupsGet();
                break;
            case 3:
                HandleGroupsGet();
                HandleGroupEdit(ReadUnsignedShort("Введiть Id групи для редагування: "));
                break;
            case 4:
                HandleGroupsGet();
                HandleGroupDelete(ReadUnsignedShort("Введiть Id групи для видалення: "));
                break;
            case 0:
                break;
            default:
                std::cout << "Невiрна опцiя.\n";
                break;
        }
    }

    void HandleWorkloadMenu()
    {
        ShowOptions();
        unsigned short option = ReadUnsignedShort("");

        switch(option){
            case 1:
                HandleWorkloadCreate();
                break;
            case 2:
                HandleWorkloadsGet();
                break;
            case 3:
                HandleWorkloadsGet();
                HandleWorkloadEdit(ReadUnsignedShort("Введiть Id навантаження для редагування: "));
                break;
            case 4:
                HandleWorkloadsGet();
                HandleWorkloadDelete(ReadUnsignedShort("Введiть Id навантаження для видалення: "));
                break;
            case 0:
                break;
            default:
                std::cout << "Невiрна опцiя.\n";
                break;
        }
    }
}
