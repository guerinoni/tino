#pragma once

#include "Block.hpp"
#include <sstream>

namespace Generator
{
    core::Byte getByte1(int n);
    core::Byte getByte2(int n);
    core::Group getGroup1(bool rw);
    core::Group getGroup2(bool rw);
    core::Group getGroup3(bool rw);
    core::Block getBlock();
    core::Block getBlock(int n, std::vector<bool> write);
} // namespace Generator

// would be nice moving all function implementation below
// to Generator.cpp without getting undefined reference

core::Byte Generator::getByte1(int n)
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

core::Byte Generator::getByte2(int n)
{
    std::vector<bool> v = {
        true, false, true, false, true, false, true, false
    };
    std::vector<std::string> s = {};

    core::Byte b(v, s, std::to_string(n) + " bytename");
    return b;
}

core::Group Generator::getGroup1(bool rw)
{
    std::vector<core::Byte> vb = { Generator::getByte1(0),
                                   Generator::getByte1(1),
                                   Generator::getByte1(2) };
    core::Group g(vb, 'm', rw);
    return g;
}

core::Group Generator::getGroup2(bool rw)
{
    std::vector<core::Byte> vb = { Generator::getByte2(3),
                                   Generator::getByte2(4),
                                   Generator::getByte2(5) };
    core::Group g(vb, 'v', rw);
    return g;
}

core::Group Generator::getGroup3(bool rw)
{
    std::vector<core::Byte> vb = { Generator::getByte2(6),
                                   Generator::getByte2(7),
                                   Generator::getByte2(8) };
    core::Group g(vb, 'j', rw);
    return g;
}

core::Block Generator::getBlock(int n, std::vector<bool> write)
{
    std::vector<core::Group> vg = { Generator::getGroup1(write[0]),
                                    Generator::getGroup2(write[1]),
                                    Generator::getGroup3(write[2]) };

    std::stringstream stream;
    stream << "blockname" << n;

    core::Block bl(vg, (n - 1) * (static_cast<int>(vg.size()) * 3),
                   stream.str());
    return bl;
}

core::Block Generator::getBlock()
{
    std::vector<core::Group> vg = { Generator::getGroup1(false),
                                    Generator::getGroup2(false),
                                    Generator::getGroup3(false) };

    std::stringstream stream;
    stream << "blockname" << 1;

    core::Block bl(vg, 0, stream.str());
    return bl;
}

