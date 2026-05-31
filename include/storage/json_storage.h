#pragma once

#include <nlohmann/json.hpp>
#include <string>

namespace storage
{
    nlohmann::json ReadJsonArray(const std::string& file_path);
    bool WriteJsonArray(const std::string& file_path, const nlohmann::json& data);
}
