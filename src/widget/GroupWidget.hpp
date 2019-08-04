#pragma once
#include "Joined.hpp"
#include "Mask.hpp"

#include <QVBoxLayout>

namespace widget
{
class GroupWidget : public QWidget
{
    Q_OBJECT

  public:
    explicit GroupWidget(core::Group *val, QWidget *parent = nullptr);
    ~GroupWidget() override          = default;

  private:
    QVBoxLayout *l;

    std::vector<std::unique_ptr<widget::Mask>> m;
    std::vector<std::unique_ptr<widget::Value>> v;
    std::unique_ptr<widget::Joined> jo;
};
} // namespace widget
