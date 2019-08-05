#include "Generator.hpp"

#include <QDebug>
#include <QtTest>

class tst_Conversion : public QObject
{
    Q_OBJECT
  private:
    core::Byte b;

  private slots:
    void initTestCase();
    void tst_BoolInt();
    void tst_IntBool();
    void tst_setIntAtAddress();
    void tst_setIntAtAddressOut();
};

void tst_Conversion::initTestCase()
{
    b = core::Generator::getByte1(0);
}

void tst_Conversion::tst_BoolInt()
{
    QCOMPARE(b.getInt(), 170);
}

void tst_Conversion::tst_IntBool()
{
    std::vector<int> v = { 0, 255, 85, 170, 6 };

    for (int i : v) {
        b.setInt(i);
        QCOMPARE(b.getInt(), i);
    }
}

void tst_Conversion::tst_setIntAtAddressOut()
{
    core::Block bl = core::Generator::getBlock();
    QVERIFY(!(bl.setIntAtAddress(6, 9))); // address 9 doesn't exist
}

void tst_Conversion::tst_setIntAtAddress()
{
    std::vector<int> v = { 0, 1, 2, 3 };
    core::Block bl     = core::Generator::getBlock();

    for (const int &i : v)
        QVERIFY(bl.setIntAtAddress(6, i));
}

QTEST_MAIN(tst_Conversion)

#include "tst_Conversion.moc"
