#pragma once

#include "Connector.hpp"
#include "MainSplitter.hpp"

class QGridLayout;
class QLineEdit;
class QTimer;

class CentralWidget : public QWidget
{
  public:
    explicit CentralWidget(QWidget *parent);
    ~CentralWidget();

    void clean();
    void stopWriteTimer();

  private:
    QGridLayout *l;

    std::vector<core::Block> blocks;
    Connector *c;

    MainSplitter *m;

    QLabel *lblPort;
    QLineEdit *linePort;
    QPushButton *btnConnect;
    QPushButton *btnWrite;
    QPushButton *btnFile;
    QLabel *lblNbytes;
    QTimer *writeTimer;

    int nBytes;
    std::string filename;
    core::Settings s;

    int btnConnectState;
};
