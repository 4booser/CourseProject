#include "ui/input.h"

#include <iostream>
#include <limits>
#include <sstream>
#include <string>

namespace
{
    bool TryParseUnsignedShort(const std::string& token, unsigned short& value)
    {
        if (token.empty())
        {
            return false;
        }

        for (char character : token)
        {
            if (character < '0' || character > '9')
            {
                return false;
            }
        }

        try
        {
            unsigned long parsed_value = std::stoul(token);

            if (parsed_value > std::numeric_limits<unsigned short>::max())
            {
                return false;
            }

            value = static_cast<unsigned short>(parsed_value);
            return true;
        }
        catch (...)
        {
            return false;
        }
    }
}

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
        while (true)
        {
            std::vector<unsigned short> ids;
            std::string line;

            std::cout << prompt;
            std::getline(std::cin, line);

            std::istringstream stream(line);
            std::string token;
            bool is_valid = true;

            while (stream >> token)
            {
                unsigned short id = 0;

                if (!TryParseUnsignedShort(token, id))
                {
                    is_valid = false;
                    break;
                }

                ids.push_back(id);
            }

            if (is_valid)
            {
                return ids;
            }

            std::cout << "Помилка. Введiть Id числами через пробiл.\n";
        }
    }
}
