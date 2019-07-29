#pragma once

#include "BtnContainer.hpp"

namespace widget
{
class HalfMask : public QWidget
{
    Q_OBJECT

  public:
    HalfMask(core::Byte val, int offset, QWidget *parent = nullptr);
    ~HalfMask() override       = default;
    HalfMask(const HalfMask &) = default;

    std::unique_ptr<BtnContainer> c;

  private:
    QHBoxLayout *l;
};
} // namespace widget