#pragma once

#include "BlockWidget.hpp"

class QVBoxLayout;
class QScrollArea;

class ScrollBlock : public QWidget
{
    Q_OBJECT

  public:
    explicit ScrollBlock(core::Block *value, QWidget *parent = nullptr);
    void refresh();

  private:
    QVBoxLayout *l;

    core::Block *val;

    widget::BlockWidget *child;

    QLabel *lBlock;
    QScrollArea *a;
};
