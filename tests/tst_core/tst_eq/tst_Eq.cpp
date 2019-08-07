#include "generator/Generator.hpp"

#include <QDebug>
#include <QtTest>

class tst_Eq : public QObject
{
    Q_OBJECT

  private slots:
    void initTestCase();
    void tst_EqBlock();
    void tst_nEqBlock();
    void tst_EqGroup();
    void tst_nEqGroup();
    void tst_EqByte();
    void tst_nEqByte();
    void tst_nByte();

  private:
    std::vector<bool> write;
};

void tst_Eq::initTestCase()
{
    write = { false, true, true };
}

void tst_Eq::tst_EqBlock()
{
    QVERIFY(Generator::getBlock(1, write) ==
            Generator::getBlock(1, write));
    QVERIFY(Generator::getBlock(2, write) ==
            Generator::getBlock(2, write));
}

void tst_Eq::tst_nEqBlock()
{
    QVERIFY(!(Generator::getBlock(1, write) ==
              Generator::getBlock(2, write)));
    QVERIFY(!(Generator::getBlock(1, write) ==
              Generator::getBlock(2, write)));
}

void tst_Eq::tst_EqGroup()
{
    QVERIFY(Generator::getGroup1(true) ==
            Generator::getGroup1(true));
    QVERIFY(Generator::getGroup2(false) ==
            Generator::getGroup2(false));
}

void tst_Eq::tst_nEqGroup()
{
    QVERIFY(!(Generator::getGroup1(true) ==
              Generator::getGroup2(true)));
    QVERIFY(!(Generator::getGroup2(false) ==
              Generator::getGroup1(false)));
}

void tst_Eq::tst_EqByte()
{
    QVERIFY(Generator::getByte1(0) == Generator::getByte1(0));
    QVERIFY(Generator::getByte2(0) == Generator::getByte2(0));
}

void tst_Eq::tst_nEqByte()
{
    QVERIFY(!(Generator::getByte1(0) == Generator::getByte2(0)));
    QVERIFY(!(Generator::getByte2(0) == Generator::getByte1(0)));
}

void tst_Eq::tst_nByte()
{
    QVERIFY(Generator::getBlock(1, write).getNbyte() == 9);
    QVERIFY(Generator::getBlock(2, write).getNbyte() == 9);
}

QTEST_MAIN(tst_Eq)

#include "tst_Eq.moc"
