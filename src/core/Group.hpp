#pragma once

#include "Byte.hpp"

namespace core
{
class Group
{
  private:
    std::vector<Byte> v;
    char type;
    bool write;

  public:
    Group(const std::vector<Byte> &v, char type, bool write);
    ~Group()             = default;
    Group(const Group &) = default;

    Group &operator=(const Group &other);
    bool operator==(const Group &other) const;
    Byte &operator[](long unsigned i);

    char getType() const;
    long unsigned getDim() const;
    bool getWrite() const;
};

} // namespace core
