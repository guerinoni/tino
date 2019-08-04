#include "HalfMask.hpp"

widget::HalfMask::HalfMask(core::Byte *val, unsigned long int offset, QWidget *parent) :
    QWidget(parent)
{
    l = new QHBoxLayout(this);

    c = std::unique_ptr<widget::BtnContainer>(
        new widget::BtnContainer(val, offset));

    for (unsigned long i = 0; i < 4; ++i) {
        c->b[i].first->setText(
            QString::fromStdString(c->val->getDesc(i + offset)));
        connect(c->b[i].first.get(), &QPushButton::clicked, this,
                c->b[i].second);

        l->addWidget(c->b[i].first.get(), 0, Qt::AlignLeft);
    }
}
