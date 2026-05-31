#include "utils/string_utils.h"

#include <algorithm>
#include <cctype>
#include <sstream>

namespace utils
{
    std::string Trim(const std::string& value)
    {
        auto first = std::find_if_not(
            value.begin(),
            value.end(),
            [](unsigned char character)
            {
                return std::isspace(character);
            }
        );

        auto last = std::find_if_not(
            value.rbegin(),
            value.rend(),
            [](unsigned char character)
            {
                return std::isspace(character);
            }
        ).base();

        if (first >= last)
        {
            return "";
        }

        return std::string(first, last);
    }

    bool IsBlank(const std::string& value)
    {
        return Trim(value).empty();
    }

    std::string JoinIds(const std::vector<unsigned short>& ids)
    {
        std::ostringstream stream;

        for (std::size_t i = 0; i < ids.size(); ++i)
        {
            stream << ids[i];

            if (i + 1 < ids.size())
            {
                stream << ',';
            }
        }

        return stream.str();
    }
}
