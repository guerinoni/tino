#include "MainSplitter.hpp"

MainSplitter::MainSplitter(std::vector<core::Block> *blocks, QWidget *parent) :
    QWidget(parent)
{
    mainlayout = new QVBoxLayout(this);
    sp         = new QSplitter(Qt::Vertical, this);

    long unsigned int cont, i;
    cont = i = 0;

    for (i = 0; i < blocks->size(); i++) {
        if (i == 0 || i % 4 == 0)
            spv.emplace_back(new QSplitter(Qt::Horizontal, this));

        blocksWidget.emplace_back(std::unique_ptr<ScrollBlock>(
            new ScrollBlock(&((*blocks)[i]), this)));
        spv[cont]->addWidget(blocksWidget[i].get());

        if (i == blocks->size() - 1 || i % 4 == 3) {
            sp->addWidget(spv[cont]);
            ++cont;
        }
        mainlayout->addWidget(sp, Qt::AlignLeft);
    }
}

void MainSplitter::updateBlock(long unsigned int i)
{
    blocksWidget[i]->refresh();
}
