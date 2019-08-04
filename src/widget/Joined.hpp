#pragma once

#include "Value.hpp"

namespace widget
{
class Joined : public QWidget
{
    Q_OBJECT

  public:
    Joined(core::Group *value, QWidget *parent);
    ~Joined() override = default;

  private:
    QBoxLayout *l;

    core::Group *val;

    std::vector<QLabel *> lbl;
    QSpinBox *box;

    int dim;
};
} // namespace widget
