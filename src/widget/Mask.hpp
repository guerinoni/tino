#pragma once

#include "HalfMask.hpp"

class QVBoxLayout;

class QLabel;

namespace widget
{
class Mask : public QWidget
{
    Q_OBJECT

  public:
    Mask(core::Byte *val, bool write, QWidget *parent = nullptr);
    ~Mask() override   = default;

    QString getStyleBtn(unsigned long int i);
    bool valAt(unsigned long int i);
    void clickBtn(unsigned long int i);

  private:
    QVBoxLayout *l;
    std::vector<std::unique_ptr<HalfMask>> m;
    QLabel *lblName;
};
} // namespace widget
