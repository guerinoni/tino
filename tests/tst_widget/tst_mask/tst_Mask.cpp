#include "Generator.hpp"
#include "Mask.hpp"

#include <QtTest>

class tst_Mask : public QObject
{
    Q_OBJECT

  private:
    widget::Mask *m;
    core::Byte b;

    QString getClr(const int i);

  private slots:
    void initTestCase();
    void tst_color();
    void tst_click();
    void tst_name();
};

void tst_Mask::initTestCase()
{
    b = core::Generator::getByte1(0);
    m = new widget::Mask(&b, true, nullptr);
}

QString tst_Mask::getClr(const int i)
{
    QString cmp = m->getStyleBtn(i);
    cmp         = cmp.mid(cmp.indexOf("background-color:"),
                  widget::BtnContainer::clrOn.length());
    return cmp;
}

void tst_Mask::tst_color()
{
    for (int i = 0; i < 8; ++i)
        QCOMPARE(getClr(i), (i % 2 == 0) ? widget::BtnContainer::clrOn
                                         : widget::BtnContainer::clrOff);
}

void tst_Mask::tst_click()
{
    for (int i = 0; i < 8; ++i) {
        bool val = m->valAt(i);

        m->clickBtn(i);

        QCOMPARE(val ? widget::BtnContainer::clrOff
                     : widget::BtnContainer::clrOn,
                 getClr(i));
        QCOMPARE((!val), m->valAt(i));
    }
}

void tst_Mask::tst_name()
{
    QCOMPARE(m->getName(), QString::fromStdString(b.getName()));
}

QTEST_MAIN(tst_Mask)

#include "tst_Mask.moc"
