#pragma once

#include "Byte.hpp"

class UWord final : public Element
{
public:
    UWord() = delete;
    explicit UWord(QString name, QString descr, uint16_t addr, uint16_t value);
    explicit UWord(QString name, QString descr, uint16_t addr);
    UWord(const UWord &) = default;
    UWord(UWord &&) = default;
    ~UWord() override = default;

    UWord &operator=(const UWord &other) = default;
    UWord &operator=(UWord &&other) = default;

    uint16_t uValue() const override;
    int16_t sValue() const override;

    void setValue(int16_t value) override;
    void setValue(uint16_t value) override;

private:
    uint16_t m_value;
};

class SWord final : public Element
{
public:
    SWord() = delete;
    explicit SWord(QString name, QString descr, uint16_t addr, int16_t value);
    explicit SWord(QString name, QString descr, uint16_t addr);
    SWord(const SWord &) = default;
    SWord(SWord &&) = default;
    ~SWord() override = default;

    SWord &operator=(const SWord &other) = default;
    SWord &operator=(SWord &&other) = default;

    uint16_t uValue() const override;
    int16_t sValue() const override;

    void setValue(int16_t value) override;
    void setValue(uint16_t value) override;

private:
    int16_t m_value;
};
