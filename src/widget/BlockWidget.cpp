#include "BlockWidget.hpp"

#include <QVBoxLayout>

widget::BlockWidget::BlockWidget(core::Block *val, QWidget *parent) :
    QWidget(parent)
{
    l = new QVBoxLayout(this);

    for (long unsigned int i = 0; i < val->getDim(); ++i) {
        g.emplace_back(std::unique_ptr<widget::GroupWidget>(
            new widget::GroupWidget(&((*val)[i]), this)));
        l->addWidget(g[i].get(), 0, Qt::AlignLeft);
    }
}
