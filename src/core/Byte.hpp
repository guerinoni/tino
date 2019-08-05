#pragma once

#include <iostream>
#include <vector>

namespace core
{
class Byte
{
  private:
    std::vector<bool> v;
    std::vector<std::string> desc;
    std::string name;

  public:
    Byte() = default;
    Byte(const std::vector<bool> &v, const std::vector<std::string> &desc,
         const std::string &name);
    ~Byte()            = default;
    Byte(const Byte &) = default;

    Byte &operator=(const Byte &other);
    bool operator==(const Byte &other) const;
    bool operator[](long unsigned i) const;

    std::string getDesc(long unsigned i) const;
    std::string getName() const;
    int getInt() const;

    void set(long unsigned i);
    void setInt(int n);
};
} // namespace core
