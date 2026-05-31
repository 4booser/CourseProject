#include "ui/input.h"

#include <iostream>
#include <limits>
#include <sstream>

namespace ui
{
    unsigned int ReadUnsignedInt(const std::string& prompt)
    {
        unsigned int value = 0;

        std::cout << prompt;

        while (!(std::cin >> value))
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Помилка. Введiть число: ";
        }

        return value;
    }

    unsigned short ReadUnsignedShort(const std::string& prompt)
    {
        unsigned short value = 0;

        std::cout << prompt;

        while (!(std::cin >> value))
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Помилка. Введiть число: ";
        }

        return value;
    }

    std::vector<unsigned short> ReadUnsignedShortList(const std::string& prompt)
    {
        std::vector<unsigned short> ids;
        std::string line;

        std::cout << prompt;
        std::getline(std::cin, line);

        std::istringstream stream(line);
        unsigned short id = 0;

        while (stream >> id)
        {
            ids.push_back(id);
        }

        return ids;
    }
}
