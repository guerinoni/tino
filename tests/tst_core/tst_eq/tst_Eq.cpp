#include "Generator.hpp"

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
    QVERIFY(generator::getBlock(1, write) == generator::getBlock(1, write));
    QVERIFY(generator::getBlock(2, write) == generator::getBlock(2, write));
}

void tst_Eq::tst_nEqBlock()
{
    QVERIFY(!(generator::getBlock(1, write) == generator::getBlock(2, write)));
    QVERIFY(!(generator::getBlock(1, write) == generator::getBlock(2, write)));
}

void tst_Eq::tst_EqGroup()
{
    QVERIFY(generator::getGroup1(true) == generator::getGroup1(true));
    QVERIFY(generator::getGroup2(false) == generator::getGroup2(false));
}

void tst_Eq::tst_nEqGroup()
{
    QVERIFY(!(generator::getGroup1(true) == generator::getGroup2(true)));
    QVERIFY(!(generator::getGroup2(false) == generator::getGroup1(false)));
}

void tst_Eq::tst_EqByte()
{
    QVERIFY(generator::getByte1(0) == generator::getByte1(0));
    QVERIFY(generator::getByte2(0) == generator::getByte2(0));
}

void tst_Eq::tst_nEqByte()
{
    QVERIFY(!(generator::getByte1(0) == generator::getByte2(0)));
    QVERIFY(!(generator::getByte2(0) == generator::getByte1(0)));
}

void tst_Eq::tst_nByte()
{
    QVERIFY(generator::getBlock(1, write).getNbyte() == 9);
    QVERIFY(generator::getBlock(2, write).getNbyte() == 9);
}

QTEST_MAIN(tst_Eq)

#include "tst_Eq.moc"
