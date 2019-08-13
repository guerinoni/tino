#pragma once

#include "Block.hpp"

#include <sstream>

namespace generator
{
core::Byte getByte1(int n);
core::Byte getByte2(int n);
core::Group getGroup1(bool rw);
core::Group getGroup2(bool rw);
core::Group getGroup3(bool rw);
core::Block getBlock();
core::Block getBlock(int n, std::vector<bool> write);
} // namespace generator

// would be nice moving all function implementation below
// to generator.cpp without getting undefined reference

core::Byte generator::getByte1(int n)
{
    std::vector<bool> v = {
        true, false, true, false, true, false, true, false
    };
    std::vector<std::string> s = { "bitname1", "bitname2", "bitname3",
                                   "bitname4", "bitname5", "bitname6",
                                   "bitname7", "bitname8" };

    core::Byte b(v, s, std::to_string(n) + " bytename");
    return b;
}

core::Byte generator::getByte2(int n)
{
    std::vector<bool> v = {
        true, false, true, false, true, false, true, false
    };
    std::vector<std::string> s = {};

    core::Byte b(v, s, std::to_string(n) + " bytename");
    return b;
}

core::Group generator::getGroup1(bool rw)
{
    std::vector<core::Byte> vb = { generator::getByte1(0),
                                   generator::getByte1(1),
                                   generator::getByte1(2) };
    core::Group g(vb, 'm', rw);
    return g;
}

core::Group generator::getGroup2(bool rw)
{
    std::vector<core::Byte> vb = { generator::getByte2(3),
                                   generator::getByte2(4),
                                   generator::getByte2(5) };
    core::Group g(vb, 'v', rw);
    return g;
}

core::Group generator::getGroup3(bool rw)
{
    std::vector<core::Byte> vb = { generator::getByte2(6),
                                   generator::getByte2(7),
                                   generator::getByte2(8) };
    core::Group g(vb, 'j', rw);
    return g;
}

core::Block generator::getBlock(int n, std::vector<bool> write)
{
    std::vector<core::Group> vg = { generator::getGroup1(write[0]),
                                    generator::getGroup2(write[1]),
                                    generator::getGroup3(write[2]) };

    std::stringstream stream;
    stream << "blockname" << n;

    core::Block bl(vg, (n - 1) * (static_cast<int>(vg.size()) * 3),
                   stream.str());
    return bl;
}

core::Block generator::getBlock()
{
    std::vector<core::Group> vg = { generator::getGroup1(false),
                                    generator::getGroup2(false),
                                    generator::getGroup3(false) };

    std::stringstream stream;
    stream << "blockname" << 1;

    core::Block bl(vg, 0, stream.str());
    return bl;
}
