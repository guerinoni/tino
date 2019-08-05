#include "Mask.hpp"

#include <QLabel>
#include <QVBoxLayout>

widget::Mask::Mask(core::Byte *val, bool write, QWidget *parent) :
    QWidget(parent)
{
    l = new QVBoxLayout(this);
    lblName =
        new QLabel(QString::fromStdString(val->getName()), this, Qt::Widget);
    l->addWidget(lblName, Qt::AlignVCenter);

    for (unsigned long int i = 0; i < 2; ++i) {
        m.push_back(std::unique_ptr<widget::HalfMask>(
            new widget::HalfMask(val, i * 4, this)));
        m[i].get()->setEnabled(write);
        l->addWidget(m[i].get(), 0, Qt::AlignVCenter);
    }
}

bool widget::Mask::valAt(unsigned long int i)
{
    return (m[0]->c->val->operator[](i));
}

QString widget::Mask::getStyleBtn(unsigned long int i)
{
    return m[i / 4]->c->b[i % 4].first->styleSheet();
}

void widget::Mask::clickBtn(unsigned long int i)
{
    m[i / 4]->c->b[i % 4].first->click();
}

QString widget::Mask::getName()
{
    return lblName->text();
}
