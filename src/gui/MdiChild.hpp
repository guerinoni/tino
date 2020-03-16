#pragma once

#include <Block.hpp>
#include <QWidget>

struct GuiElement
{
    Element *el;
    std::vector<QWidget *> w;
};

class MdiChild : public QWidget
{
    Q_OBJECT

public:
    explicit MdiChild(const Block &block, QWidget *parent = nullptr);

    bool hasElementWithAddress(int address) const;

signals:
    void updateModbus(int address);

public slots:
    void updateGuiElemets();

private:
    std::vector<int> m_addresses;
    std::vector<GuiElement> m_guiElements;
};
