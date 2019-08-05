#pragma once

#include "Block.hpp"
#include "GroupWidget.hpp"

class QVBoxLayout;

namespace widget
{
class BlockWidget : public QWidget
{
    Q_OBJECT

  public:
    explicit BlockWidget(core::Block *val, QWidget *parent = nullptr);
    ~BlockWidget() override = default;

  private:
    QVBoxLayout *l;

    std::vector<std::unique_ptr<widget::GroupWidget>> g;
};
} // namespace widget
