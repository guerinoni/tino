#include "MdiChild.hpp"

#include "Led.hpp"
#include "ValueWidget.hpp"

#include <Bitset.hpp>
#include <Byte.hpp>
#include <Word.hpp>
#include <QGridLayout>
#include <QGroupBox>
#include <QMetaEnum>
#include <QScrollArea>

MdiChild::MdiChild(const Block &block, QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle(block.description);
    setLayout(new QGridLayout);

    auto r = 0;
    auto c = 0;

    for (const auto &element : block.elements) {
        auto groupBox = new QGroupBox(this);
        groupBox->setTitle(element->description() + " - 0x"
                           + QString::number(element->address(), 16) + " - "
                           + QMetaEnum::fromType<Element::Type>().valueToKey(element->type()));
        groupBox->setLayout(new QGridLayout);

        if (auto bitset = dynamic_cast<Bitset *>(element.get())) {
            auto leds = std::vector<QWidget *>();
            for (size_t i = 0; i < Bitset::size; ++i) {
                if (c == 4) {
                    ++r;
                    c = 0;
                }
                ++c;

                auto led = new Led(bitset->names().at(static_cast<int>(i)),
                                   this,
                                   QSize(30, 30),
                                   bitset->valueAt(i) ? Led::State::On : Led::State::Off);
                led->attachBitset(bitset, i);
                connect(led, &Led::bitsetStateChanged, this, &MdiChild::updateModbus);
                leds.emplace_back(led);

                dynamic_cast<QGridLayout *>(groupBox->layout())->addWidget(led, r, c);
            }
            m_guiElements.emplace_back(GuiElement{element.get(), leds});
        } else {
            auto w = new ValueWidget(element.get(), element->sValue(), element->name());
            connect(w, &ValueWidget::valueChanged, this, &MdiChild::updateModbus);
            m_guiElements.emplace_back(GuiElement{element.get(), {w}});
            dynamic_cast<QGridLayout *>(groupBox->layout())->addWidget(w, r, c);
        }

        m_addresses.emplace_back(element->address());
        layout()->addWidget(groupBox);
    }
}

bool MdiChild::hasElementWithAddress(int address) const
{
    auto it = std::find_if(m_addresses.begin(), m_addresses.end(), [&](const auto &add) {
        return (add == address);
    });
    return (it != m_addresses.end());
}

void MdiChild::updateGuiElemets()
{
    for (const auto &guiElement : m_guiElements) {
        if (auto bitset = dynamic_cast<Bitset *>(guiElement.el)) {
            for (size_t i = 0; i < Bitset::size; ++i) {
                if (auto led = dynamic_cast<Led *>(guiElement.w.at(i))) {
                    auto state = bitset->valueAt(i) ? Led::State::On : Led::State::Off;
                    led->setState(state);
                }
            }
            continue;
        } else if (auto vw = dynamic_cast<ValueWidget *>(guiElement.w.front())) {
            vw->updateValue(guiElement.el->sValue());
        }
    }
}
