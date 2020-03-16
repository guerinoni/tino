#include "Byte.hpp"

UByte::UByte(QString name, QString descr, uint16_t addr)
    : Element{std::move(name), std::move(descr), addr}
{
    setType(Element::Type::UByte);
}

UByte::UByte(QString name, QString descr, uint16_t addr, uint8_t value)
    : Element{std::move(name), std::move(descr), addr}
    , m_value{value}
{
    setType(Element::Type::UByte);
}

uint16_t UByte::uValue() const
{
    return static_cast<uint16_t>(m_value);
}

int16_t UByte::sValue() const
{
    return static_cast<int16_t>(m_value);
}

void UByte::setValue(int16_t value)
{
    if (valOutOfBound<int16_t, uint8_t>(value)) {
        throw std::logic_error("Out of bound value <int16_t, uint8_t>");
    }

    m_value = static_cast<uint8_t>(value);
}

void UByte::setValue(uint16_t value)
{
    if (valOutOfBound<uint16_t, uint8_t>(value)) {
        throw std::logic_error("Out of bound value <uint16_t, uint8_t>");
    }

    m_value = static_cast<uint8_t>(value);
}

SByte::SByte(QString name, QString descr, uint16_t addr)
    : Element{std::move(name), std::move(descr), addr}
{
    setType(Element::Type::SByte);
}

SByte::SByte(QString name, QString descr, uint16_t addr, int8_t value)
    : Element{std::move(name), std::move(descr), addr}
    , m_value{value}
{
    setType(Element::Type::SByte);
}

uint16_t SByte::uValue() const
{
    return static_cast<uint16_t>(m_value);
}

int16_t SByte::sValue() const
{
    return static_cast<int16_t>(m_value);
}

void SByte::setValue(int16_t value)
{
    if (valOutOfBound<int16_t, int8_t>(value)) {
        throw std::logic_error("Out of bound value <int16_t, uint8_t>");
    }

    m_value = static_cast<int8_t>(value);
}

void SByte::setValue(uint16_t value)
{
    if (valOutOfBound<uint16_t, int8_t>(value)) {
        throw std::logic_error("Out of bound value <uint16_t, uint8_t>");
    }

    m_value = static_cast<int8_t>(value);
}
