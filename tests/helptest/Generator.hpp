#pragma once

#include "Block.hpp"

namespace Generator {
    core::Byte getByte1(int n);
    core::Byte getByte2(int n);
    core::Group getGroup1(bool rw);
    core::Group getGroup2(bool rw);
    core::Group getGroup3(bool rw);
    core::Block getBlock();
    core::Block getBlock(int n, std::vector<bool> write);
}
