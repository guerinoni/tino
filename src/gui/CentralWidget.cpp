#include "CentralWidget.hpp"

#include "Parser.hpp"

CentralWidget::CentralWidget(QWidget *parent) : QWidget(parent)
{
    l          = new QGridLayout(this);
    m          = nullptr;
    c          = nullptr;
    writeTimer = nullptr;
    filename   = "";

    // label port:
    lblPort = new QLabel(this);
    lblPort->setText("Port: ");
    l->addWidget(lblPort, 0, 0, Qt::AlignLeft);
    l->setColumnStretch(0, 0);

    // edit the modbus port name
    linePort = new QLineEdit(this);
    l->addWidget(linePort, 0, 1, Qt::AlignLeft);
    l->setColumnStretch(1, 0);

    // button that starts connection
    btnConnect = new QPushButton(this);
    btnConnect->setText("connect");
    l->addWidget(btnConnect, 0, 2, Qt::AlignLeft);
    l->setColumnStretch(2, 0);

    btnConnectState = 0;
    // 0: disconnected, 1: connected, 2: connected to auto opened serialport

    // connect
    connect(btnConnect, &QPushButton::clicked, this, [&]() {
        if (c) {
            if (btnConnectState == 0) {
                core::Parser::getSettings(filename, s);

                if (!linePort->text().isEmpty()) // take portname from gui
                    s.portName = linePort->text().toStdString();
                else { // take portname from file
                    if (s.portName == "auto") {
                        s.portName      = Connector::openPort();
                        btnConnectState = 2;
                    }
                    linePort->setText(QString::fromStdString(s.portName));
                }
                if (c->startConnection(s)) {
                    btnConnect->setText("disconect");
                    if (btnConnectState != 2)
                        btnConnectState = 1;
                }
            } else {
                btnConnect->setText("connect");
                c->endConnection();

                if (btnConnectState == 2) {
                    Connector::closePort();
                    linePort->setText("");
                }
                btnConnectState = 0;
            }
            lblNbytes->setText("0 bytes written");
            stopWriteTimer();
        }
    });

    // button that begins writing on modbus
    btnWrite = new QPushButton(this);
    btnWrite->setText("write");
    l->addWidget(btnWrite, 0, 3, Qt::AlignLeft);
    l->setColumnStretch(3, 0);
    // write blocks
    connect(btnWrite, &QPushButton::clicked, this, [&]() {
        if (c && c->isConnected()) {
            if (btnWrite->text() == "write") {
                writeTimer = new QTimer();
                connect(writeTimer, &QTimer::timeout, this, [this]() {
                    nBytes = 0;

                    for (long unsigned int i = 0; i < blocks.size(); ++i)
                        nBytes += c->writeBlock(i);

                    QString s = QString("%1 bytes written").arg(nBytes);
                    lblNbytes->setText(s);
                });
                writeTimer->start(s.refreshTime);
                btnWrite->setText("stop");
            } else
                stopWriteTimer();
        }
    });

    // button that loads json
    btnFile = new QPushButton(this);
    btnFile->setText("load file");
    l->addWidget(btnFile, 0, 4, Qt::AlignLeft);
    l->setColumnStretch(4, 0);
    // draw blocks
    connect(btnFile, &QPushButton::clicked, this, [&]() {
        filename = QFileDialog::getOpenFileName(this, tr("Open config"), "/",
                                                tr("json Files (*.json)"))
                       .toStdString();

        if (filename.empty())
            return;

        blocks.erase(blocks.begin(), blocks.end());
        core::Parser::parse(filename, blocks);

        c = nullptr;
        lblNbytes->setText("0 bytes written");

        clean();
        c = new Connector(&blocks, this);
        m = new MainSplitter(&blocks, this);

        l->addWidget(m, 1, 0, 1, 6, Qt::AlignLeft);

        connect(c, &Connector::updateBlockReq, this,
                [this](long unsigned int ii) {
                    m->updateBlock(ii);
                    qDebug() << blocks[ii][0][0].getInt();
                });
    });

    // nBytes
    lblNbytes = new QLabel(this);
    lblNbytes->setText("0 bytes written");
    l->addWidget(lblNbytes, 0, 5, Qt::AlignLeft);
    l->setColumnStretch(5, 2);
}

void CentralWidget::clean()
{
    stopWriteTimer();

    if (c) {
        c->endConnection();
        delete c;
        c = nullptr;
    }
    if (m) {
        delete m;
        m = nullptr;
    }
}

void CentralWidget::stopWriteTimer()
{
    if (writeTimer) {
        writeTimer->stop();
        delete writeTimer;
        writeTimer = nullptr;
    }
    if (btnWrite)
        btnWrite->setText("write");
}

CentralWidget::~CentralWidget()
{
    clean();
}
