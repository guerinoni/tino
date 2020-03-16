#pragma once

#include "Element.hpp"

#include <bitset>
#include <QStringList>

class Bitset final : public Element
{
public:
    Bitset() = delete;
    explicit Bitset(QString name, QString descr, uint16_t addr);
    Bitset(const Bitset &) = default;
    Bitset(Bitset &&) = default;
    ~Bitset() override = default;

    Bitset &operator=(const Bitset &other) = default;
    Bitset &operator=(Bitset &&other) = default;

    void setAt(size_t index, bool value, QString name = {}, QString description = {});
    bool valueAt(size_t index) const;

    uint16_t uValue() const override;
    int16_t sValue() const override;

    void setValue(int16_t value) override;
    void setValue(uint16_t value) override;

    const QStringList &descriptions() const noexcept;

    const QStringList &names() const noexcept;

    constexpr static size_t size = 8;

private:
    QStringList m_bitsNames{{}, {}, {}, {}, {}, {}, {}, {}};
    QStringList m_bitsDescriptions{{}, {}, {}, {}, {}, {}, {}, {}};
    std::bitset<size> m_bits{};
};
