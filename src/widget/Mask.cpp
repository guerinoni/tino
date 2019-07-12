#include "Mask.hpp"

Mask::Mask(core::Byte val, QWidget *parent) : QWidget(parent)
{
    QGridLayout *l = new QGridLayout(this);

    c      = std::unique_ptr<BtnContainer>(new BtnContainer);
    c->val = val;

    //    std::for_each(c->b.begin(), c->b.end(), [l, this](int &i) {
    //        c->b[i].first->setGeometry(i, 0, 100, 50);
    //        c->setClr(i);

    //        c->b[i].first->setText(
    //            QString::fromStdString(c->val.getDescription(i)));

    //        connect(c->b[i].first.get(), &QPushButton::clicked, this,
    //                c->b[i].second);

    //        l->addWidget(c->b[i].first.get(), 1, i, Qt::AlignVCenter);
    //    });
}

bool Mask::valAt(const int i)
{
    return c->val[i];
}

QString Mask::getStyleBtn(const int i)
{
    return c->b[i].first->styleSheet();
}
