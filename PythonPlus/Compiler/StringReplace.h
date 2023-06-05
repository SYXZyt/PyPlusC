#pragma once
#include <string>
#include <regex>

static inline void StringReplace(std::string& str, const std::string& from, const std::string& to)
{
    if (from.empty())
        return;

    str = std::regex_replace(str, std::regex(from), to);
}