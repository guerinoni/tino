#include "Element.hpp"

Element::Element(QString name, QString descr, uint16_t addr) :
    m_name{ std::move(name) }, m_description{ std::move(descr) }, m_address{
        addr
    }
{
}

bool Element::operator==(const Element &other) const
{
    return description() == other.description() && address() == other.address();
}

bool Element::operator!=(const Element &other) const
{
    return !(*this == other);
}

Element::Type Element::type() const
{
    return m_type;
}

void Element::setType(const Element::Type &type)
{
    m_type = type;
}

QString Element::name() const
{
    return m_name;
}

QString Element::description() const
{
    return m_description;
}

uint16_t Element::address() const
{
    return m_address;
}

void Element::setAddress(const uint16_t &address, const uint16_t &offset)
{
    m_address = address + offset;
}

uint16_t Element::uValue() const
{
    throw std::logic_error("Undefined function");
}

int16_t Element::sValue() const
{
    throw std::logic_error("Undefined function");
}

void Element::setValue(uint16_t value)
{
    (void)value;
    throw std::logic_error("Undefined function");
}

void Element::setValue(int16_t value)
{
    (void)value;
    throw std::logic_error("Undefined function");
}
