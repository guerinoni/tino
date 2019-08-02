#include "Generator.hpp"

#include <QDebug>
#include <QtTest>

class tst_Eq : public QObject
{
    Q_OBJECT

  private slots:
    void tst_EqBlock();
    void tst_nEqBlock();
    void tst_EqGroup();
    void tst_nEqGroup();
    void tst_EqByte();
    void tst_nEqByte();
    void tst_nByte();

  private:
};

void tst_Eq::tst_EqBlock()
{
    QVERIFY(core::Generator::getBlock(1) == core::Generator::getBlock(1));
    QVERIFY(core::Generator::getBlock(2) == core::Generator::getBlock(2));
}

void tst_Eq::tst_nEqBlock()
{
    QVERIFY(!(core::Generator::getBlock(1) == core::Generator::getBlock(2)));
    QVERIFY(!(core::Generator::getBlock(2) == core::Generator::getBlock(1)));
}

void tst_Eq::tst_EqGroup()
{
    QVERIFY(core::Generator::getGroup1(true) ==
            core::Generator::getGroup1(true));
    QVERIFY(core::Generator::getGroup2(false) ==
            core::Generator::getGroup2(false));
}

void tst_Eq::tst_nEqGroup()
{
    QVERIFY(!(core::Generator::getGroup1(true) ==
              core::Generator::getGroup2(true)));
    QVERIFY(!(core::Generator::getGroup2(false) ==
              core::Generator::getGroup1(false)));
}

void tst_Eq::tst_EqByte()
{
    QVERIFY(core::Generator::getByte1(0) == core::Generator::getByte1(0));
    QVERIFY(core::Generator::getByte2(0) == core::Generator::getByte2(0));
}

void tst_Eq::tst_nEqByte()
{
    QVERIFY(!(core::Generator::getByte1(0) == core::Generator::getByte2(0)));
    QVERIFY(!(core::Generator::getByte2(0) == core::Generator::getByte1(0)));
}

void tst_Eq::tst_nByte()
{
    QVERIFY(core::Generator::getBlock(1).getNbyte() == 9);
    QVERIFY(core::Generator::getBlock(2).getNbyte() == 9);
}

QTEST_MAIN(tst_Eq)

#include "tst_Eq.moc"
