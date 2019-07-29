#include "CentralWidget.hpp"

CentralWidget::CentralWidget(QWidget *parent) : QWidget(parent)
{
    l        = new QGridLayout(this);
    m        = nullptr;
    c        = nullptr;
    filename = "";

    // top
    lblPort = new QLabel(this);
    lblPort->setText("Port: ");
    l->addWidget(lblPort, 0, 0, Qt::AlignLeft);
    l->setColumnStretch(0, 0);

    linePort = new QLineEdit(this);
    l->addWidget(linePort, 0, 1, Qt::AlignLeft);
    l->setColumnStretch(1, 0);

    btnConnect = new QPushButton(this);
    btnConnect->setText("connect");
    l->addWidget(btnConnect, 0, 2, Qt::AlignLeft);
    l->setColumnStretch(2, 0);

    // connect
    connect(btnConnect, &QPushButton::clicked, this, [&]() {
        if (c) {
            if (btnConnect->text() == "connect") {
                if (c->startConnection(linePort->text(), filename))
                    btnConnect->setText("disconect");
                linePort->setText(c->getLinePortText());
            } else {
                btnConnect->setText("connect");
                c->endConnection();
            }
            lblNbytes->setText("0 bytes written");
        }
    });

    // write something
    btnWrite = new QPushButton(this);
    btnWrite->setText("write");
    l->addWidget(btnWrite, 0, 3, Qt::AlignLeft);
    l->setColumnStretch(3, 0);

    connect(btnWrite, &QPushButton::clicked, this, [&]() {
        nBytes = 0;

        for (long unsigned int i = 0; i < blocks.size(); ++i)
            nBytes += c->writeBlock(i);

        QString s = QString("%1 bytes written").arg(nBytes);
        lblNbytes->setText(s);
    });

    // load file
    btnFile = new QPushButton(this);
    btnFile->setText("load file");
    l->addWidget(btnFile, 0, 4, Qt::AlignLeft);
    l->setColumnStretch(4, 0);

    // draw blocks
    connect(btnFile, &QPushButton::clicked, this, [&]() {
        filename = QFileDialog::getOpenFileName(this, tr("Open config"), "/",
                                                tr("json Files (*.json)"))
                       .toStdString();

        if (filename.length() <= 0)
            return;

        blocks = core::Parser::parse(filename);

        c = nullptr;
        lblNbytes->setText("0 bytes written");

        if (blocks.size() <= 0)
            return;

        if (c) {
            c->endConnection();
            delete c;
            c = nullptr;
        }
        if (m) {
            delete m;
            m = nullptr;
        }
        c = new Connector(&blocks, this);
        m = new MainSplitter(blocks, this);

        l->addWidget(m, 1, 0, 1, 6, Qt::AlignLeft);

        connect(c, &Connector::updateBlockReq, this,
                [this](long unsigned int ii) { m->updateBlock(ii); });
    });

    // nBytes
    lblNbytes = new QLabel(this);
    lblNbytes->setText("0 bytes written");
    l->addWidget(lblNbytes, 0, 5, Qt::AlignLeft);
    l->setColumnStretch(5, 2);
}