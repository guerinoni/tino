#pragma once

#include "Block.hpp"

namespace core
{
struct Generator {
    Generator()  = delete;
    ~Generator() = default;

    static core::Byte getByte1(int n);
    static core::Byte getByte2(int n);
    static core::Group getGroup1(bool rw);
    static core::Group getGroup2(bool rw);
    static core::Group getGroup3(bool rw);
    static core::Block getBlock();
    static core::Block getBlock(int n, std::vector<bool> write);
};
} // namespace core
