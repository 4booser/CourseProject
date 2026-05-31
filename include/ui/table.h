#pragma once

#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

namespace ui
{
    inline void PrintSectionTitle(const std::string& title)
    {
        std::cout << "\n=== " << title << " ===\n";
    }

    inline void PrintSeparator(std::size_t length)
    {
        std::cout << std::string(length, '-') << '\n';
    }

    template <typename... Values>
    void PrintRow(const std::vector<int>& widths, const Values&... values)
    {
        std::size_t index = 0;
        ((std::cout << std::left << std::setw(widths[index++]) << values), ...);
        std::cout << '\n';
    }
}
