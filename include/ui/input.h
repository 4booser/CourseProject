#pragma once

#include <string>
#include <vector>

namespace ui
{
    unsigned int ReadUnsignedInt(const std::string& prompt);
    unsigned short ReadUnsignedShort(const std::string& prompt);
    std::vector<unsigned short> ReadUnsignedShortList(const std::string& prompt);
}
