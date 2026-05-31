#pragma once

#include <string>
#include <utility>

struct OperationResult
{
    bool success = false;
    std::string message;

    static OperationResult Ok()
    {
        return {true, ""};
    }

    static OperationResult Fail(std::string error_message)
    {
        return {false, std::move(error_message)};
    }
};
