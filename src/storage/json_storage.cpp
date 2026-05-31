#include "storage/json_storage.h"

#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;
using json = nlohmann::json;

namespace storage
{
    json ReadJsonArray(const std::string& file_path)
    {
        std::ifstream input_file(file_path);

        if (!input_file.is_open())
        {
            return json::array();
        }

        json data;

        try
        {
            input_file >> data;
        }
        catch (...)
        {
            return json::array();
        }

        if (!data.is_array())
        {
            return json::array();
        }

        return data;
    }

    bool WriteJsonArray(const std::string& file_path, const json& data)
    {
        fs::path path(file_path);
        fs::create_directories(path.parent_path());

        std::ofstream output_file(file_path);

        if (!output_file.is_open())
        {
            return false;
        }

        output_file << data.dump(2);
        return true;
    }
}
