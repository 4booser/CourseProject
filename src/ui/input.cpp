#include "ui/input.h"

#include <iostream>
#include <limits>
#include <sstream>
#include <string>

#ifdef _WIN32
#ifndef NOMINMAX
#define NOMINMAX
#endif
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <vector>
#endif

namespace
{
#ifdef _WIN32
    std::wstring Utf8ToWide(const std::string& value)
    {
        if (value.empty())
        {
            return L"";
        }

        int size = MultiByteToWideChar(CP_UTF8, 0, value.data(), static_cast<int>(value.size()), nullptr, 0);
        if (size <= 0)
        {
            return L"";
        }

        std::wstring result(static_cast<std::size_t>(size), L'\0');
        MultiByteToWideChar(CP_UTF8, 0, value.data(), static_cast<int>(value.size()), result.data(), size);
        return result;
    }

    std::string WideToUtf8(const std::wstring& value)
    {
        if (value.empty())
        {
            return "";
        }

        int size = WideCharToMultiByte(CP_UTF8, 0, value.data(), static_cast<int>(value.size()), nullptr, 0, nullptr, nullptr);
        if (size <= 0)
        {
            return "";
        }

        std::string result(static_cast<std::size_t>(size), '\0');
        WideCharToMultiByte(CP_UTF8, 0, value.data(), static_cast<int>(value.size()), result.data(), size, nullptr, nullptr);
        return result;
    }

    bool IsConsoleInput()
    {
        HANDLE input = GetStdHandle(STD_INPUT_HANDLE);
        if (input == INVALID_HANDLE_VALUE || input == nullptr)
        {
            return false;
        }

        DWORD mode = 0;
        return GetConsoleMode(input, &mode) != 0;
    }

    void WriteUtf8Prompt(const std::string& prompt)
    {
        HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
        DWORD mode = 0;

        if (output != INVALID_HANDLE_VALUE && output != nullptr && GetConsoleMode(output, &mode) != 0)
        {
            std::wstring wide_prompt = Utf8ToWide(prompt);
            DWORD written = 0;
            WriteConsoleW(output, wide_prompt.data(), static_cast<DWORD>(wide_prompt.size()), &written, nullptr);
            return;
        }

        std::cout << prompt;
    }

    std::string ReadConsoleLineUtf8(const std::string& prompt)
    {
        WriteUtf8Prompt(prompt);

        HANDLE input = GetStdHandle(STD_INPUT_HANDLE);
        std::wstring result;
        wchar_t buffer[512];

        while (true)
        {
            DWORD read = 0;
            if (!ReadConsoleW(input, buffer, static_cast<DWORD>(std::size(buffer) - 1), &read, nullptr))
            {
                return "";
            }

            buffer[read] = L'\0';
            result.append(buffer, buffer + read);

            if (!result.empty() && (result.back() == L'\n' || result.back() == L'\r'))
            {
                break;
            }
        }

        while (!result.empty() && (result.back() == L'\n' || result.back() == L'\r'))
        {
            result.pop_back();
        }

        return WideToUtf8(result);
    }
#endif

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

            if (parsed_value > (std::numeric_limits<unsigned short>::max)())
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
        std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
    }

    std::string ReadLine(const std::string& prompt)
    {
#ifdef _WIN32
        if (IsConsoleInput())
        {
            return ReadConsoleLineUtf8(prompt);
        }
#endif

        std::string value;

        std::cout << prompt;
        std::getline(std::cin, value);

        return value;
    }

    unsigned int ReadUnsignedInt(const std::string& prompt)
    {
        unsigned int value = 0;

#ifdef _WIN32
        WriteUtf8Prompt(prompt);
#else
        std::cout << prompt;
#endif

        while (!(std::cin >> value))
        {
            std::cin.clear();
            ClearInputLine();
#ifdef _WIN32
            WriteUtf8Prompt("Помилка. Введiть число: ");
#else
            std::cout << "Помилка. Введiть число: ";
#endif
        }

        return value;
    }

    unsigned short ReadUnsignedShort(const std::string& prompt)
    {
        unsigned short value = 0;

#ifdef _WIN32
        WriteUtf8Prompt(prompt);
#else
        std::cout << prompt;
#endif

        while (!(std::cin >> value))
        {
            std::cin.clear();
            ClearInputLine();
#ifdef _WIN32
            WriteUtf8Prompt("Помилка. Введiть число: ");
#else
            std::cout << "Помилка. Введiть число: ";
#endif
        }

        return value;
    }

    std::vector<unsigned short> ReadUnsignedShortList(const std::string& prompt)
    {
        while (true)
        {
            std::vector<unsigned short> ids;
            std::string line = ReadLine(prompt);

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

#ifdef _WIN32
            WriteUtf8Prompt("Помилка. Введiть Id числами через пробiл.\n");
#else
            std::cout << "Помилка. Введiть Id числами через пробiл.\n";
#endif
        }
    }
}
