#pragma once

#include "Block.hpp"
#include "Settings.hpp"

// json

namespace core
{
struct Parser {
    Parser()  = delete;
    ~Parser() = default;

    static std::ifstream getRoot(const std::string &name);
    static void parse(std::string name, std::vector<core::Block> &all);
    static void getSettings(std::string name, Settings &s);
};
} // namespace core
