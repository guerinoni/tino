#include "Word.hpp"

UWord::UWord(QString name, QString descr, uint16_t addr, uint16_t value) :
    Element{ std::move(name), std::move(descr), addr }, m_value{ value }
{
    setType(Element::Type::UWord);
}

UWord::UWord(QString name, QString descr, uint16_t addr) :
    Element{ name, descr, addr }, m_value{ 0 }
{
    setType(Element::Type::UWord);
}

uint16_t UWord::uValue() const
{
    return m_value;
}

int16_t UWord::sValue() const
{
    return static_cast<int16_t>(m_value);
}

void UWord::setValue(int16_t value)
{
    if (valOutOfBound<int16_t, uint16_t>(value)) {
        throw std::logic_error("Out of bound value <int16_t, uint16_t>");
    }

    m_value = static_cast<uint16_t>(value);
}

void UWord::setValue(uint16_t value)
{
    if (valOutOfBound<uint16_t, uint16_t>(value)) {
        throw std::logic_error("Out of bound value <uint16_t, uint16_t>");
    }

    m_value = value;
}

SWord::SWord(QString name, QString descr, uint16_t addr, int16_t value) :
    Element{ std::move(name), std::move(descr), addr }, m_value{ value }
{
    setType(Element::Type::SWord);
}

SWord::SWord(QString name, QString descr, uint16_t addr) :
    Element{ name, descr, addr }, m_value{ 0 }
{
    setType(Element::Type::SWord);
}

uint16_t SWord::uValue() const
{
    return static_cast<uint16_t>(m_value);
}

int16_t SWord::sValue() const
{
    return m_value;
}

void SWord::setValue(int16_t value)
{
    if (valOutOfBound<int16_t, int16_t>(value)) {
        throw std::logic_error("Out of bound value <int16_t, int16_t>");
    }

    m_value = value;
}

void SWord::setValue(uint16_t value)
{
    if (valOutOfBound<uint16_t, int16_t>(value)) {
        throw std::logic_error("Out of bound value <uint16_t, int16_t>");
    }

    m_value = static_cast<int16_t>(value);
}
