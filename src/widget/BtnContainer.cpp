#include "BtnContainer.hpp"

QString widget::BtnContainer::clrOn  = "background-color:#ff0000;";
QString widget::BtnContainer::clrOff = "background-color:#0000ff;";

widget::BtnContainer::BtnContainer(core::Byte *val, unsigned long int offset)
{
    this->offset = offset;
    this->val    = val;

    for (unsigned long int i = 0; i < 4; ++i) {
        b.emplace_back(std::make_pair(
            std::unique_ptr<QPushButton>(new QPushButton()), [i, this]() {
                this->val->set(i + this->offset);
                setClr(i);
            }));
        setClr(i);
    }
}

void widget::BtnContainer::setClr(unsigned long int i)
{
    b[i].first->setStyleSheet((*val)[i + offset] ? clrOn : clrOff);
}
