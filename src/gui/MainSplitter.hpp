#pragma once

#include "ScrollBlock.hpp"

class QSplitter;
class QVBoxLayout;

class MainSplitter : public QWidget
{
  public:
    MainSplitter(std::vector<core::Block> *blocks, QWidget *parent);
    ~MainSplitter() = default;

    void updateBlock(long unsigned int i);

  private:
    QVBoxLayout *mainlayout;

    std::vector<core::Block> *blocks;

    std::vector<std::unique_ptr<ScrollBlock>> blocksWidget;

    QSplitter *sp;
    std::vector<QSplitter *> spv;
};
