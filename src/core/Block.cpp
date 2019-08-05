#include "Block.hpp"

#include <algorithm>

core::Block::Block(const std::vector<core::Group> &v, int start,
                   const std::string &name) :
    v(v),
    name(name), start(start)
{
}

std::string core::Block::getName() const
{
    return name;
}
core::Group &core::Block::operator[](long unsigned i)
{
    return v[i];
}

long unsigned core::Block::getDim() const
{
    return v.size();
}

bool core::Block::operator==(const core::Block &other) const
{
    if ((name != other.name) || (v.size() != other.v.size()) ||
        (start != other.start))
        return false;

    long unsigned i = 0;

    while (i < v.size() && v[i] == other.v[i])
        ++i;

    return i == v.size();
}

core::Block &core::Block::operator=(const core::Block &other)
{
    this->v = other.v;

    name  = other.name;
    start = other.start;
    return *this;
}

int core::Block::getStart() const
{
    return start;
}

int core::Block::getNbyte()
{
    int n = 0;

    std::for_each(v.begin(), v.end(),
                  [&n](const core::Group &g) { n += g.getDim(); });

    return n;
}

bool core::Block::setIntAtAddress(int values, int address)
{
    int cont = this->start;

    unsigned long int i = 0, j;

    while (i < v.size()) { // scroll groups

        if (!v[i].getWrite()) { // update if is readonly
            j = 0;
            while (j < v[i].getDim()) { // scroll bytes
                if (cont == address) {
                    v[i][j].setInt(values);
                    return true;
                }
                ++cont;
                ++j;
            }
        }
        ++i;
    }
    return false;
}
