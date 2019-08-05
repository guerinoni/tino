#pragma once

#include "Byte.hpp"

#include <QLabel>

class QHBoxLayout;
class QSpinBox;

namespace widget
{
class Value : public QWidget
{
    Q_OBJECT

  public:
    Value(core::Byte *value, bool write, QWidget *parent = nullptr);
    ~Value() override = default;

    int getBoxValue();
    QString getName();

  private:
    QHBoxLayout *l;

    core::Byte *val;

    QSpinBox *box;
    QLabel *lblValue;
};
} // namespace widget
