#include "Bitset.hpp"

Bitset::Bitset(QString name, QString descr, uint16_t addr)
    : Element{std::move(name), std::move(descr), addr}
{
    setType(Element::Type::Bitset);
}

void Bitset::setAt(size_t index, bool value, QString name, QString description)
{
    m_bits.set(index, value);
    m_bitsNames[index] = std::move(name);
    m_bitsDescriptions[index] = std::move(description);
}

bool Bitset::valueAt(size_t index) const
{
    return m_bits.test(index);
}

uint16_t Bitset::uValue() const
{
    return static_cast<uint16_t>(m_bits.to_ulong());
}

int16_t Bitset::sValue() const
{
    return static_cast<int16_t>(m_bits.to_ulong());
}

void Bitset::setValue(int16_t value)
{
    if (valOutOfBound<int16_t, uint8_t>(value)) {
        throw std::logic_error("Out of bound value <int16_t, uint8_t>");
    }

    m_bits = static_cast<unsigned long long>(value);
}

void Bitset::setValue(uint16_t value)
{
    if (valOutOfBound<uint16_t, uint8_t>(value)) {
        throw std::logic_error("Out of bound value <uint16_t, uint8_t>");
    }

    m_bits = static_cast<unsigned long long>(value);
}

const QStringList &Bitset::descriptions() const noexcept
{
    return m_bitsDescriptions;
}

const QStringList &Bitset::names() const noexcept
{
    return m_bitsNames;
}

static_assert(Bitset::size == 8, "Is the size of bit changed?");
