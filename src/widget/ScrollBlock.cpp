#include "ScrollBlock.hpp"

#include <QScrollArea>
#include <QVBoxLayout>

ScrollBlock::ScrollBlock(core::Block *value, QWidget *parent) : QWidget(parent)
{
    this->val = value;
    l         = new QVBoxLayout(this);

    lBlock = new QLabel(this);
    lBlock->setText(QString::fromStdString(val->getName()));
    lBlock->setMinimumHeight(20);
    lBlock->setStyleSheet("QLabel { background-color: white; color: black; }");

    child = new widget::BlockWidget(val, this);
    child->setMaximumWidth(1000);

    a = nullptr;
    refresh();

    l->addWidget(lBlock, 0, Qt::AlignHCenter);
    l->addWidget(a);

    this->setMinimumWidth(50);
}

void ScrollBlock::refresh()
{
    if (a) {
        delete a->takeWidget();
        child = nullptr;
    } else {
        a = new QScrollArea(this);
        a->setWidget(child);
    }
    child = new widget::BlockWidget(val, this);
    child->setMaximumWidth(1000);
    a->setWidget(child);
}
