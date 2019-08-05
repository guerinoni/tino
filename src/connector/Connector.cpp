#include "Connector.hpp"

#include <QDebug>
#include <QModbusRtuSerialSlave>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <thread>

Connector::Connector(std::vector<core::Block> *v, QObject *parent) :
    QObject(parent)
{
    server = new QModbusRtuSerialSlave(this);
    all    = v;

    short unsigned int sz = 0;
    for (core::Block &bl : (*all))
        sz += static_cast<quint16>(bl.getNbyte());

    QModbusDataUnitMap reg;
    reg.insert(QModbusDataUnit::HoldingRegisters,
               { QModbusDataUnit::HoldingRegisters, (*all)[0].getStart(), sz });

    server->setMap(reg);

    connect(server, &QModbusServer::dataWritten, this,
            [this](QModbusDataUnit::RegisterType table, int address, int size) {
                QModbusDataUnit u(table, address,
                                  static_cast<unsigned short>(size));
                // unit contains one HoldingRegisters

                if (!server->data(&u))
                    qDebug() << "cannot server->data()";

                long unsigned int i =
                    0; // find in which block data were written
                while ((i < all->size()) &&
                       (*all)[i].getStart() <= u.startAddress())
                    ++i;

                --i;
                qDebug() << "i: " << i << ", value: " << u.value(0)
                         << ", address: " << u.startAddress()
                         << ", size: " << u.valueCount();

                for (int j = 0; j < static_cast<int>(u.valueCount()); ++j)
                    (*all)[i].setIntAtAddress(
                        static_cast<unsigned short>(u.value(j)),
                        static_cast<unsigned short>(u.startAddress() + j));
                emit updateBlockReq(i);
            });
}

Connector::~Connector()
{
    endConnection();

    delete server;
    server = nullptr;
}

bool Connector::startConnection(const core::Settings &s)
{
    if (server) {
        // set server parameter

        server->setConnectionParameter(QModbusDevice::SerialPortNameParameter,
                                       QString::fromStdString(s.portName));
        server->setConnectionParameter(QModbusDevice::SerialParityParameter,
                                       s.Parity);
        server->setConnectionParameter(QModbusDevice::SerialBaudRateParameter,
                                       s.BaudRate);
        server->setConnectionParameter(QModbusDevice::SerialDataBitsParameter,
                                       s.DataBits);
        server->setConnectionParameter(QModbusDevice::SerialStopBitsParameter,
                                       s.StopBits);
        server->setServerAddress(s.ServerAddress);

        // connect server
        if (!server->connectDevice())
            qDebug() << "cannot connect server";

        qDebug() << "error: " << server->errorString();
        qDebug() << "state: " << server->state();

        return (server->state() == QModbusRtuSerialSlave::ConnectedState);
    } // end if (server && portname.length() > 0)
    return false;
}

void Connector::endConnection()
{
    if (server)
        server->disconnectDevice();
}

int Connector::writeBlock(long unsigned int a)
{
    int cont = -1;

    if (server) {
        ++cont;
        for (unsigned long i = 0; i < (*all)[a].getDim(); ++i) {
            for (unsigned long j = 0; j < (*all)[a][i].getDim(); ++j) {
                if ((*all)[a][i].getWrite()) {
                    if (!server->setData(QModbusDataUnit::HoldingRegisters,
                                         static_cast<unsigned short>(
                                             (*all)[a].getStart() + cont),
                                         static_cast<unsigned short>(
                                             (*all)[a][i][j].getInt())))
                        qDebug() << "error writing data: " << cont << " "
                                 << server->errorString();
                }
                ++cont;
            }
        }
    }
    return cont;
}

bool Connector::isConnected()
{
    return (server->state() == QModbusServer::ConnectedState);
}

std::string Connector::openPort()
{
    closePort();

    // socat output path
    qDebug() << "env: " << QString::fromStdString(std::getenv("HOME"));
    char outFile[300] = "";
    strcat(outFile, std::getenv("HOME"));
    strcat(outFile, "/.tino/socatOutput.txt");
    qDebug() << "outfile: " << QString::fromStdString(outFile);

    // start socat
    std::thread([outFile]() {
        char socat[300] = "rm ";
        strcat(socat, outFile);
        system(socat);

        socat[0] = '\0';
        strcat(socat, "socat -d -d -lf ");
        strcat(socat, outFile);
        strcat(socat, " pty,raw,echo=0 pty,raw,echo=0");
        system(socat);
    })
        .detach();

    std::fstream socatOutput;
    socatOutput.open(outFile, std::ifstream::in);
    std::string ret;
    std::string found;

    bool stop = true;
    do {
        std::string temp;

        while (getline(socatOutput, temp)) {
            if (temp.find("starting data transfer loop with FDs") ==
                std::string::npos)
                stop = false;
        }
        socatOutput.clear();
        socatOutput.seekg(0, std::ios::beg);
    } while (stop);
    system("sleep 0.1");

    // read socat output
    for (int i = 0; i < 2; ++i) {
        std::string temp;
        getline(socatOutput, temp);
        qDebug() << "temp: " << QString::fromStdString(temp);
        found = temp.substr(temp.find("/dev/pts/", 0), 10);

        if (ret.empty())
            ret = found;
        else {
            //            char toWrite[300] = "notify-send \"connect your client
            //            to "; strcat(toWrite, found.c_str()); strcat(toWrite,
            //            "\""); system(toWrite);

            //            toWrite[0] = '\0';
            char toWrite[300] = "";
            strcat(toWrite, "echo \"");
            strcat(toWrite, found.c_str());
            strcat(toWrite, "\" > ");
            strcat(toWrite, std::getenv("HOME"));
            strcat(toWrite, "/.tino/clientPort.txt");
            system(toWrite);
        }
    }
    return ret;
}

void Connector::closePort()
{
    system("killall socat");
}
