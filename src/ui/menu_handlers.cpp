#include "ui/menu_handlers.h"

#include "headers/teacher.h"
#include "headers/workload.h"
#include "headers/discipline.h"
#include "headers/group.h"
#include "ui.h"
#include "ui/input.h"

#include <iostream>
#include <string>

namespace
{
    using CreateHandler = void (*)();
    using PrintHandler = void (*)();
    using EditHandler = void (*)(const unsigned short&);
    using DeleteHandler = void (*)(const unsigned short&);

    void HandleCrudMenu(
        const std::string& edit_prompt,
        const std::string& delete_prompt,
        CreateHandler create_handler,
        PrintHandler print_handler,
        EditHandler edit_handler,
        DeleteHandler delete_handler)
    {
        ui::ShowOptions();
        unsigned short option = ui::ReadUnsignedShort("");

        switch (option)
        {
            case 1:
                create_handler();
                break;
            case 2:
                print_handler();
                break;
            case 3:
                print_handler();
                edit_handler(ui::ReadUnsignedShort(edit_prompt));
                break;
            case 4:
                print_handler();
                delete_handler(ui::ReadUnsignedShort(delete_prompt));
                break;
            case 0:
                break;
            default:
                std::cout << "Невiрна опцiя.\n";
                break;
        }
    }
}

namespace ui
{
    void HandleTeacherMenu()
    {
        HandleCrudMenu(
            "Введiть Id викладача для редагування: ",
            "Введiть Id викладача для видалення: ",
            HandleTeacherCreate,
            HandleTeachersPrint,
            HandleTeacherEdit,
            HandleTeacherDelete);
    }

    void HandleDisciplineMenu()
    {
        HandleCrudMenu(
            "Введiть Id дисциплiни для редагування: ",
            "Введiть Id дисциплiни для видалення: ",
            HandleDisciplineCreate,
            HandleDisciplinesGet,
            HandleDisciplineEdit,
            HandleDisciplineDelete);
    }

    void HandleGroupMenu()
    {
        HandleCrudMenu(
            "Введiть Id групи для редагування: ",
            "Введiть Id групи для видалення: ",
            HandleGroupCreate,
            HandleGroupsGet,
            HandleGroupEdit,
            HandleGroupDelete);
    }

    void HandleWorkloadMenu()
    {
        HandleCrudMenu(
            "Введiть Id навантаження для редагування: ",
            "Введiть Id навантаження для видалення: ",
            HandleWorkloadCreate,
            HandleWorkloadsGet,
            HandleWorkloadEdit,
            HandleWorkloadDelete);
    }
}
