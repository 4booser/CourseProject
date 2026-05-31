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
}
