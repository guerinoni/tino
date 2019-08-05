#pragma once

#include "GroupWidget.hpp"

namespace widget
{
class BlockWidget : public QWidget
{
    Q_OBJECT

  public:
    explicit BlockWidget(core::Block *val, QWidget *parent = nullptr);
    ~BlockWidget() override                     = default;

  private:
    QBoxLayout *l;

    std::vector<std::unique_ptr<widget::GroupWidget>> g;
};
} // namespace widget
