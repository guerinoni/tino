#include "Value.hpp"

#include <QHBoxLayout>
#include <QSpinBox>

widget::Value::Value(core::Byte *value, bool write, QWidget *parent) :
    QWidget(parent)
{
    this->val = value;
    l         = new QHBoxLayout(this);
    lblValue =
        new QLabel(QString::fromStdString(val->getName()), this, Qt::Widget);

    box = new QSpinBox(this);
    box->setMinimum(0);
    box->setMaximum(255);
    box->setValue(static_cast<int>(val->getInt()));
    box->setEnabled(write);

    connect(box, &QSpinBox::editingFinished, this,
            [this]() { val->setInt(box->value()); });

    l->addWidget(box, 0, Qt::AlignVCenter);
    l->addWidget(lblValue, 0, Qt::AlignVCenter);
}

int widget::Value::getBoxValue()
{
    return box->value();
}

QString widget::Value::getName()
{
    return lblValue->text();
}
