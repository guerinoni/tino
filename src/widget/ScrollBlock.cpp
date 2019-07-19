#include "ScrollBlock.hpp"

ScrollBlock::ScrollBlock(core::Block val, QWidget *parent) : QWidget(parent)
{
    l = new QVBoxLayout(this);

    lBlock = new QLabel(this);
    lBlock->setText(QString::fromStdString(val.getName()));
    lBlock->setMinimumHeight(50);

    child = new BlockWidget(val, this);
    child->setMaximumWidth(1000);

    a = new QScrollArea(this);
    a->setWidget(child);

    l->addWidget(lBlock, 0, Qt::AlignLeft);
    l->addWidget(a);
}