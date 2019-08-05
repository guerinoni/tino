#pragma once

#include "Group.hpp"

namespace core
{
class Block
{
  private:
    std::vector<core::Group> v;
    std::string name;
    int start;

  public:
    Block(const std::vector<core::Group> &v, int start, const std::string &name);
    ~Block()             = default;
    Block(const Block &) = default;

    Block &operator=(const Block &other);
    bool operator==(const Block &other) const;
    core::Group &operator[](long unsigned i);

    int getStart() const;
    long unsigned getDim() const;
    std::string getName() const;
    int getNbyte();

    bool setIntAtAddress(int values, int address);
};

} // namespace core
