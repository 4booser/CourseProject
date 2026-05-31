#include "ui/input.h"

#include <iostream>
#include <limits>
#include <sstream>

namespace ui
{
    void ClearInputLine()
    {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    std::string ReadLine(const std::string& prompt)
    {
        std::string value;

        std::cout << prompt;
        std::getline(std::cin, value);

        return value;
    }

    unsigned int ReadUnsignedInt(const std::string& prompt)
    {
        unsigned int value = 0;

        std::cout << prompt;

        while (!(std::cin >> value))
        {
            std::cin.clear();
            ClearInputLine();
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
            ClearInputLine();
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
