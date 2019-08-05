#include "Joined.hpp"

#include <QHBoxLayout>
#include <QLabel>
#include <QSpinBox>
#include <cmath>

widget::Joined::Joined(core::Group *value, QWidget *parent) : QWidget(parent)
{
    this->val = value;
    l         = new QHBoxLayout(this);

    box = new QSpinBox(this);
    box->setMinimum(0);
    box->setMaximum(static_cast<int>(pow(2, (8 * val->getDim()) - 1)));
    box->setEnabled(val->getWrite());
    l->addWidget(box, 0, Qt::AlignVCenter);

    long v = 0;
    for (unsigned long int i = 0; i < val->getDim(); ++i) {
        lbl.emplace_back(new QLabel(QString::fromStdString((*val)[i].getName()),
                                    this, Qt::Widget));
        l->addWidget(lbl[i], 0, Qt::AlignVCenter);
        v += (*val)[i].getInt();
    }
    box->setValue(static_cast<int>(v));

    connect(box, &QSpinBox::editingFinished, this, [&]() {
        int spinValue = box->value();
        for (unsigned long int i = 0; i < val->getDim(); ++i) {
            (*val)[i].setInt(spinValue > 255 ? 255 : spinValue);
            spinValue -= 255;
        }
    });
}
