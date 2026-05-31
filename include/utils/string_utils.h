#pragma once

#include <algorithm>
#include <cctype>
#include <string>
#include <vector>

namespace utils
{
    inline std::string Trim(const std::string& value);

    inline bool IsBlank(const std::string& value);

    inline std::string JoinIds(const std::vector<unsigned short>& ids);
}
