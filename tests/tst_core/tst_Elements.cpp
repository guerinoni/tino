#include "../../src/core/Bitset.hpp"
#include "../../src/core/Word.hpp"

#include <QtTest>

class tst_Elements : public QObject
{
    Q_OBJECT

private slots:
    void checkBitset();
    void checkByte();
    void checkWord();
};

void tst_Elements::checkBitset()
{
    int16_t value = 47;
    Bitset b{{}, {}, {}};

    b.setValue(value);
    QCOMPARE(b.valueAt(0), 1);
    QCOMPARE(b.valueAt(1), 1);
    QCOMPARE(b.valueAt(2), 1);
    QCOMPARE(b.valueAt(3), 1);
    QCOMPARE(b.valueAt(4), 0);
    QCOMPARE(b.valueAt(5), 1);
    QCOMPARE(b.valueAt(6), 0);
    QCOMPARE(b.valueAt(7), 0);

    value = 53;
    b.setAt(0, true);
    b.setAt(1, false);
    b.setAt(2, true);
    b.setAt(3, false);
    b.setAt(4, true);
    b.setAt(5, true);
    b.setAt(6, false);
    b.setAt(7, false);
    QCOMPARE(b.sValue(), value);
    QCOMPARE(b.descriptions().size(), Bitset::size);
}

void tst_Elements::checkByte()
{
    UByte b{"name", "description", 0x90, 99};
    QCOMPARE(b.name(), "name");
    QCOMPARE(b.description(), "description");
    QCOMPARE(b.address(), 0x90);
    QCOMPARE(b.uValue(), 99);

    SByte bNeg{"rewq", "rewq", 0xA0, -127};
    QCOMPARE(bNeg.name(), "rewq");
    QCOMPARE(bNeg.description(), "rewq");
    QCOMPARE(bNeg.address(), 0xA0);
    QCOMPARE(bNeg.sValue(), -127);
}

void tst_Elements::checkWord()
{
    uint16_t uv = 4320;
    UWord w{{}, {}, {}, uv};
    QCOMPARE(w.sValue(), 4320);

    int16_t sv= -2043;
    SWord sw{"", "", 0x11, -2043};
    QCOMPARE(sw.sValue(), sv);
}

QTEST_APPLESS_MAIN(tst_Elements)

#include "tst_Elements.moc"
