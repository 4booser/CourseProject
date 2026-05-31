#include "utils/string_utils.h"

#include <sstream>

namespace utils
{
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

    inline std::string Trim(const std::string& value)
    {
        auto first = std::find_if_not(value.begin(), value.end(), [](unsigned char character) {
            return std::isspace(character);
        });

        auto last = std::find_if_not(value.rbegin(), value.rend(), [](unsigned char character) {
            return std::isspace(character);
        }).base();

        if (first >= last)
        {
            return "";
        }

        return std::string(first, last);
    }

    inline bool IsBlank(const std::string& value)
    {
        return Trim(value).empty();
    }

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
