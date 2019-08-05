#pragma once

#include "BtnContainer.hpp"

class QHBoxLayout;

namespace widget
{
class HalfMask : public QWidget
{
    Q_OBJECT

  public:
    HalfMask(core::Byte *val, unsigned long int offset,
             QWidget *parent = nullptr);
    ~HalfMask() override = default;

    std::unique_ptr<widget::BtnContainer> c;

  private:
    QHBoxLayout *l;
};
} // namespace widget
