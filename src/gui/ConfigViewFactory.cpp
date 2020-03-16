#include "ConfigViewFactory.hpp"

#include <Bitset.hpp>
#include <QDockWidget>
#include <QStandardItemModel>
#include <QTreeView>

QDockWidget *ConfigViewFactory::makeConfigView(const Protocol &prot)
{
    auto dock = new QDockWidget("Protocol");
    dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    auto view = new QTreeView(dock);
    auto model = new QStandardItemModel(view);

    const auto root = model->invisibleRootItem();
    auto blockId = 0;
    for (const auto &b : prot.blocks) {
        auto blockItem = new QStandardItem(b.description);
        blockItem->setFlags(blockItem->flags() & ~Qt::ItemIsEditable);
        blockItem->setWhatsThis(QStringLiteral("block_%1").arg(blockId));
        blockItem->setAccessibleText(guiCreatable);
        auto groupId = 0;
        for (const auto &element : b.elements) {
            auto groupElement = makeItem(element.get());
            groupElement->setWhatsThis(QStringLiteral("block_%1_group_%2").arg(groupId++));

            if (auto bitset = dynamic_cast<Bitset *>(element.get())) {
                for (size_t i = 0; i < Bitset::size; ++i) {
                    auto str = bitset->descriptions()[i].isEmpty() ? QString("item_%1").arg(i)
                                                                   : bitset->descriptions()[i];
                    auto bit = new QStandardItem(str);
                    bit->setFlags(bit->flags() & ~Qt::ItemIsEditable);
                    groupElement->appendRow(bit);
                }
            }
            blockItem->appendRow(groupElement);
        }

        ++blockId;
        root->appendRow(blockItem);
    }

    view->setModel(model);
    dock->setWidget(view);
    return dock;
}

QStandardItem *ConfigViewFactory::makeItem(Element *element)
{
    const auto d = element->description();
    const auto str = d.isEmpty() ? QString("item_" + QString::number(m_emptyItemCounter++)) : d;
    auto item = new QStandardItem(str);
    item->setFlags(item->flags() & ~Qt::ItemIsEditable);
    return item;
}
