#pragma once

#include "Element.hpp"

class UByte final : public Element
{
  public:
    UByte() = delete;
    explicit UByte(QString name, QString descr, uint16_t addr);
    explicit UByte(QString name, QString descr, uint16_t addr, uint8_t value);
    UByte(const UByte &) = default;
    UByte(UByte &&)      = default;
    ~UByte() override    = default;

    UByte &operator=(const UByte &other) = default;
    UByte &operator=(UByte &&other) = default;

    uint16_t uValue() const override;
    int16_t sValue() const override;

    void setValue(int16_t value) override;
    void setValue(uint16_t value) override;

  private:
    uint8_t m_value{};
};

class SByte final : public Element
{
  public:
    SByte() = delete;
    explicit SByte(QString name, QString descr, uint16_t addr);
    explicit SByte(QString name, QString descr, uint16_t addr, int8_t value);
    SByte(const SByte &) = default;
    SByte(SByte &&)      = default;
    ~SByte() override    = default;

    SByte &operator=(const SByte &other) = default;
    SByte &operator=(SByte &&other) = default;

    uint16_t uValue() const override;
    int16_t sValue() const override;

    void setValue(int16_t value) override;
    void setValue(uint16_t value) override;

  private:
    int8_t m_value{};
};
