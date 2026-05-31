#include "storage/json_storage.h"

#include <exception>
#include <filesystem>
#include <fstream>
#include <iostream>

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
        catch (const std::exception& exception)
        {
            std::cerr << "JSON read error in file '" << file_path << "': "
                << exception.what() << '\n';
            return json::array();
        }

        if (!data.is_array())
        {
            std::cerr << "JSON format error in file '" << file_path
                << "': expected array as root element.\n";
            return json::array();
        }

        return data;
    }

    bool WriteJsonArray(const std::string& file_path, const json& data)
    {
        try
        {
            fs::path path(file_path);
            fs::create_directories(path.parent_path());

            std::ofstream output_file(file_path);

            if (!output_file.is_open())
            {
                std::cerr << "JSON write error: cannot open file '" << file_path << "'.\n";
                return false;
            }

            output_file << data.dump(2);
            return true;
        }
        catch (const std::exception& exception)
        {
            std::cerr << "JSON write error in file '" << file_path << "': "
                << exception.what() << '\n';
            return false;
        }
    }
}
