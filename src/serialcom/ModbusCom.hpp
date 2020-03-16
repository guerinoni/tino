#pragma once

#include <Protocol.hpp>
#include <Settings.hpp>
#include <memory>
#include <QModbusServer>
#include <QObject>

class ModbusCom : public QObject
{
    Q_OBJECT

public:
    explicit ModbusCom(const Protocol &protocol, QObject *parent = nullptr);

    bool isConnected() const;
    bool connectModbus(const Settings &settings);
    bool disconnectModbus();

    void writeRegister(int address);

signals:
    void updateGui(int address);

private slots:
    void handleError(const QString &errorString, QModbusDevice::Error error);
    void updateRegisters(QModbusDataUnit::RegisterType table, int address, int size);

private:
    std::unique_ptr<QModbusServer> m_modbusDevice;
    const Protocol &m_protocol;

    bool initializeServer();
};
