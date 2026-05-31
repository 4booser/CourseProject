#pragma once

#include <string>
#include <vector>

namespace utils
{
    inline std::string JoinIds(const std::vector<unsigned short>& ids)
    {
        std::string result;

        for (std::size_t i = 0; i < ids.size(); ++i)
        {
            result += std::to_string(ids[i]);

            if (i + 1 < ids.size())
            {
                result += ',';
            }
        }

        return result;
    }
}
