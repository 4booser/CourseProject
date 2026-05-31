#pragma once

#include <string>
#include <vector>

namespace ui
{
    void ClearInputLine();
    std::string ReadLine(const std::string& prompt);
    unsigned int ReadUnsignedInt(const std::string& prompt);
    unsigned short ReadUnsignedShort(const std::string& prompt);
    std::vector<unsigned short> ReadUnsignedShortList(const std::string& prompt);
}
