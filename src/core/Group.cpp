#include "Group.hpp"

/*
 * m: mask
 * v: value
 * j: joined
 */

core::Group::Group(std::vector<core::Byte> v, char type)
{
    this->v    = v;
    this->type = type;
}

core::Group::Group(std::vector<bool> v, std::vector<std::string> description,
                   bool rw, char type)
{
    this->type = type = type;
    this->add(v, description, rw);
}

void core::Group::add(std::vector<bool> v, std::vector<std::string> description,
                      bool rw)
{
    core::Byte tv(v, description, rw);
    this->v[v.size() - 1] = tv;
}

char core::Group::getType()
{
    return type;
}

core::Byte &core::Group::operator[](const int i)
{
    return v[i];
}

int core::Group::getDim()
{
    return v.size();
}

core::Group &core::Group::operator=(const Group &other)
{
    this->type = other.type;

    this->v = other.v;
    return *this;
}

bool core::Group::operator==(const core::Group &other) const
{
    if ((type != other.type) || (v.size() != other.v.size()))
        return false;

    int i = 0;

    while (i < v.size() && v[i] == other.v[i])
        ++i;

    return i == v.size() ? true : false;
}
