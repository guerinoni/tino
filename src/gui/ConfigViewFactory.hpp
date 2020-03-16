#pragma once

#include <Protocol.hpp>

class QDockWidget;
class QStandardItem;

class Element;

class ConfigViewFactory
{
public:
    QDockWidget *makeConfigView(const Protocol &prot);

    constexpr static auto guiCreatable{"guiCreatable"};

private:
    int m_emptyItemCounter;

    QStandardItem *makeItem(Element *element);
};
