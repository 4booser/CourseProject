#pragma once

#include <string>
#include <vector>

namespace utils
{
    std::string Trim(const std::string& value);

    bool IsBlank(const std::string& value);

    std::string JoinIds(const std::vector<unsigned short>& ids);
}
