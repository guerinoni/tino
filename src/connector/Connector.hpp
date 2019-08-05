#pragma once

#include "Block.hpp"
#include "Settings.hpp"

#include <QObject>

class QModbusRtuSerialSlave; // forward declaration

class Connector : public QObject
{
    Q_OBJECT
  private:
    QModbusRtuSerialSlave *server;
    std::vector<core::Block> *all;
    QString portname;

  public:
    Connector(std::vector<core::Block> *v, QObject *parent);
    ~Connector();

    bool startConnection(const core::Settings &s);
    void endConnection();

    int writeBlock(long unsigned int a);
    QString getLinePortText();
    bool isConnected();

    static std::string openPort();
    static void closePort();

  signals:
    void updateBlockReq(long unsigned int);
};
