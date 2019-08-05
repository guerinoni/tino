#include "Generator.hpp"

#include <sstream>

core::Byte core::Generator::getByte1(int n)
{
    std::vector<bool> v = {
        true, false, true, false, true, false, true, false
    };
    std::vector<std::string> s = {
        "bitname1", "bitname2", "bitname3", "bitname4",
        "bitname5", "bitname6", "bitname7", "bitname8",
    };

    core::Byte b(v, s, std::to_string(n) + " bytename");
    return b;
}

core::Byte core::Generator::getByte2(int n)
{
    std::vector<bool> v = {
        true, false, true, false, true, false, true, false
    };
    std::vector<std::string> s = {};

    core::Byte b(v, s, std::to_string(n) + " bytename");
    return b;
}

core::Group core::Generator::getGroup1(bool rw)
{
    std::vector<core::Byte> vb = { getByte1(0), getByte1(1), getByte1(2) };
    core::Group g(vb, 'm', rw);
    return g;
}

core::Group core::Generator::getGroup2(bool rw)
{
    std::vector<core::Byte> vb = { getByte2(3), getByte2(4), getByte2(5) };
    core::Group g(vb, 'v', rw);
    return g;
}
core::Group core::Generator::getGroup3(bool rw)
{
    std::vector<core::Byte> vb = { getByte2(6), getByte2(7), getByte2(8) };
    core::Group g(vb, 'j', rw);
    return g;
}

core::Block core::Generator::getBlock(int n, std::vector<bool> write)
{
    std::vector<core::Group> vg = { getGroup1(write[0]), getGroup2(write[1]),
                                    getGroup3(write[2]) };

    std::stringstream stream;
    stream << "blockname" << n;

    core::Block bl(vg, (n - 1) * (static_cast<int>(vg.size()) * 3),
                   stream.str());
    return bl;
}

core::Block core::Generator::getBlock()
{
    std::vector<core::Group> vg = { getGroup1(false), getGroup2(false),
                                    getGroup3(false) };

    std::stringstream stream;
    stream << "blockname" << 1;

    core::Block bl(vg, 0, stream.str());
    return bl;
}
