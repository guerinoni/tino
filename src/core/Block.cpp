#include "Block.hpp"

#include <Element.hpp>

bool Block::operator==(const Block &other) const
{
    auto d = description == other.description;
    auto a = address == other.address;
    auto c = category == other.category;
    auto size = elements.size() == other.elements.size();
    if (!d || !size || !a || !c) {
        return false;
    }

    for (size_t i = 0; i < elements.size(); ++i) {
        if (*elements.at(i) != *other.elements.at(i)) {
            return false;
        }
    }

    return true;
}
