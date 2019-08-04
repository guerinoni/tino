#include "Group.hpp"

/*
 * m: mask
 * v: value
 * j: joined
 */

core::Group::Group(const std::vector<Byte> &v, char type, bool write) : v(v), type(type), write(write) {}

char core::Group::getType() const
{
    return type;
}

core::Byte &core::Group::operator[](long unsigned i)
{
    return v[i];
}

long unsigned core::Group::getDim() const
{
    return v.size();
}

core::Group &core::Group::operator=(const Group &other)
{
    this->type  = other.type;
    this->write = other.write;
    this->v     = other.v;
    return *this;
}

bool core::Group::operator==(const core::Group &other) const
{
    if ((write != other.write) || (type != other.type) ||
        (v.size() != other.v.size()))
        return false;

    unsigned long i = 0;

    while (i < v.size() && v[i] == other.v[i])
        ++i;

    return i == v.size();
}

bool core::Group::getWrite() const
{
    return write;
}
