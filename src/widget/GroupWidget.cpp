#include "GroupWidget.hpp"

#include <QDebug>

widget::GroupWidget::GroupWidget(core::Group *val, QWidget *parent) :
    QWidget(parent)
{
    l = new QVBoxLayout(this);
    long unsigned int i;

    switch (val->getType()) {
        case 'm': // mask
            for (i = 0; i < val->getDim(); ++i) {
                m.emplace_back(std::unique_ptr<widget::Mask>(
                    new widget::Mask(&(*val)[i], val->getWrite(), this)));
                l->addWidget(m[static_cast<unsigned long>(i)].get(), 0,
                             Qt::AlignHCenter);
            }
            break;
        case 'v': // value
            for (i = 0; i < val->getDim(); ++i) {
                v.emplace_back(std::unique_ptr<widget::Value>(
                    new widget::Value(&((*val)[i]), val->getWrite(), this)));
                l->addWidget(v[static_cast<unsigned long>(i)].get(), 0,
                             Qt::AlignHCenter);
            }
            break;
        case 'j': // joined
            jo = std::unique_ptr<widget::Joined>(new widget::Joined(val, this));
            l->addWidget(jo.get(), 0, Qt::AlignHCenter);
            break;
        default:
            qDebug() << val->getType() << " is not a type";
            break;
    } // end switch (val->getType())
}
