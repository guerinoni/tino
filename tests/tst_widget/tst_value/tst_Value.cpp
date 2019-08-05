#include "Generator.hpp"
#include "Value.hpp"

#include <QtTest>

class tst_Value : public QObject
{
    Q_OBJECT

  private:
    widget::Value *v;
    core::Byte b;

  private slots:
    void initTestCase();
    void tst_boxValue();
    void tst_name();
};

void tst_Value::initTestCase()
{
    b = core::Generator::getByte1(0);
    v = new widget::Value(&b, true, nullptr);
}

void tst_Value::tst_boxValue()
{
    QCOMPARE(v->getBoxValue(), b.getInt());
}

void tst_Value::tst_name()
{
    QCOMPARE(v->getName(), QString::fromStdString(b.getName()));
}

QTEST_MAIN(tst_Value)

#include "tst_Value.moc"
