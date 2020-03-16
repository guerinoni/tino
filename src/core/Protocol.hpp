#pragma once

#include "Block.hpp"

#include <unordered_map>

class Protocol
{
public:
    bool operator==(const Protocol &other) const;

    std::vector<Block> blocks;
    std::unordered_map<int, Element *> elementMap;
};
