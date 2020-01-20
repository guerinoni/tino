#pragma once

#include <QString>

class Element
{
  public:
    enum class Type {
        Bitset,
        UByte,
        SByte,
        UWord,
        SWord,

        UndefinedType = -1
    };

    Element() = default;
    explicit Element(QString name, QString descr, uint16_t addr);
    Element(const Element &) = default;
    Element(Element &&)      = default;
    virtual ~Element()       = default;

    bool operator==(const Element &other) const;
    bool operator!=(const Element &other) const;

    Element &operator=(const Element &other) = default;
    Element &operator=(Element &&other) = default;

    Element::Type type() const;
    void setType(const Element::Type &type);

    QString name() const;
    void setName(const QString &name);

    QString description() const;
    void setDescription(const QString &description);

    uint16_t address() const;
    void setAddress(const uint16_t &address, const uint16_t &offset = 0);

    template<typename T, typename K> bool valOutOfBound(const T &val)
    {
        return val < std::numeric_limits<K>::min() ||
               val > std::numeric_limits<K>::max();
    }

    virtual uint16_t uValue() const;
    virtual int16_t sValue() const;

    virtual void setValue(uint16_t value);
    virtual void setValue(int16_t value);

  protected:
    Element::Type m_type{ Element::Type::UndefinedType };
    QString m_name{};
    QString m_description{};
    uint16_t m_address{ 0 };
};
