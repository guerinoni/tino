#pragma once

#include "Group.hpp"

#include <QLabel>

class QHBoxLayout;
class QSpinBox;

namespace widget
{
class Joined : public QWidget
{
    Q_OBJECT

  public:
    Joined(core::Group *value, QWidget *parent);
    ~Joined() override = default;

  private:
    QHBoxLayout *l;

    core::Group *val;

    std::vector<QLabel *> lbl;
    QSpinBox *box;

    int dim;
};
} // namespace widget
