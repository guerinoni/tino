#include "DialogAbout.hpp"

#include "ui_DialogAbout.h"

DialogAbout::DialogAbout(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DialogAbout)
{
    ui->setupUi(this);

    connect(ui->pushButton, &QPushButton::clicked, this, [&]() { close(); });
}

DialogAbout::~DialogAbout()
{
    delete ui;
}
