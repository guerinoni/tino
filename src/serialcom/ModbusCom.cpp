#include "ModbusCom.hpp"

#include <Bitset.hpp>
#include <Element.hpp>

#include <QDebug>
#include <QModbusRtuSerialSlave>

ModbusCom::ModbusCom(const Protocol &protocol, QObject *parent)
    : QObject(parent)
    , m_modbusDevice{std::make_unique<QModbusRtuSerialSlave>()}
    , m_protocol{protocol}
{
    connect(m_modbusDevice.get(),
            &QModbusServer::errorOccurred,
            this,
            [this](QModbusDevice::Error error) {
                handleError(m_modbusDevice->errorString(), error);
            });
    connect(m_modbusDevice.get(), &QModbusServer::dataWritten, this, &ModbusCom::updateRegisters);

    initializeServer();
}

bool ModbusCom::isConnected() const
{
    return (m_modbusDevice->state() == QModbusDevice::ConnectedState);
}

bool ModbusCom::connectModbus(const Settings &settings)
{
    if (m_modbusDevice->state() == QModbusDevice::ConnectedState) {
        qDebug() << "ModbusCom: Modbus already connected.";
        return false;
    }

    m_modbusDevice->setConnectionParameter(QModbusDevice::SerialPortNameParameter,
                                           settings.portName);
    m_modbusDevice->setConnectionParameter(QModbusDevice::SerialBaudRateParameter,
                                           settings.baudRate);
    m_modbusDevice->setConnectionParameter(QModbusDevice::SerialDataBitsParameter,
                                           settings.dataBits);
    m_modbusDevice->setConnectionParameter(QModbusDevice::SerialParityParameter, settings.parity);
    m_modbusDevice->setConnectionParameter(QModbusDevice::SerialStopBitsParameter,
                                           settings.stopBits);
    m_modbusDevice->setServerAddress(1);

    if (!m_modbusDevice->connectDevice()) {
        qCritical() << "ModbusCom: Modbus connection failed: " << m_modbusDevice->errorString();
        return false;
    }

    qDebug() << "ModbusCom: Modbus connected succesfully.";
    return true;
}

bool ModbusCom::disconnectModbus()
{
    if (m_modbusDevice->state() != QModbusDevice::ConnectedState) {
        qDebug() << "ModbusCom: Modbus not connected.";
        return false;
    }

    m_modbusDevice->disconnectDevice();
    return true;
}

void ModbusCom::writeRegister(int address)
{
    m_modbusDevice->disconnect();
    m_modbusDevice->setData(QModbusDataUnit::HoldingRegisters,
                            address,
                            m_protocol.elementMap.at(address)->uValue());
    connect(m_modbusDevice.get(), &QModbusServer::dataWritten, this, &ModbusCom::updateRegisters);
}

void ModbusCom::handleError(const QString &errorString, QModbusDevice::Error error)
{
    if (error == QModbusDevice::NoError || !m_modbusDevice) {
        return;
    }

    qWarning() << QStringLiteral("ModbusCom: Error occurred: %1 (code 0x%2)")
                      .arg(errorString)
                      .arg(error);

    switch (error) {
    case QModbusDevice::NoError:
        break;
    case QModbusDevice::ReadError:
        break;
    case QModbusDevice::WriteError:
        break;
    case QModbusDevice::ConnectionError:
        break;
    case QModbusDevice::ConfigurationError:
        break;
    case QModbusDevice::TimeoutError:
        break;
    case QModbusDevice::ProtocolError:
        break;
    case QModbusDevice::ReplyAbortedError:
        break;
    case QModbusDevice::UnknownError:
        break;
    }
}

void ModbusCom::updateRegisters(QModbusDataUnit::RegisterType table, int address, int size)
{
    for (auto i = 0; i < size; ++i) {
        quint16 value;
        quint16 add = static_cast<quint16>(address + i);

        if (table != QModbusDataUnit::HoldingRegisters) {
            continue;
        }

        m_modbusDevice->data(QModbusDataUnit::HoldingRegisters, static_cast<quint16>(add), &value);

        if (m_protocol.elementMap.find(add) == m_protocol.elementMap.end()) {
            qWarning() << "Address is invalid (" << add << ")";
        }

        auto el = m_protocol.elementMap.at(add);

        if (const auto type = el->type(); type == Element::Type::Bitset) {
            const auto h = static_cast<int16_t>((value & 0xff00) >> 8);
            if (const auto bitset = dynamic_cast<Bitset *>(el)) {
                bitset->setValue(h);
                Q_EMIT updateGui(bitset->address());
            }

            const auto lowAdd = add + 1;
            if (m_protocol.elementMap.find(lowAdd) != m_protocol.elementMap.end()) {
                const auto l = static_cast<int16_t>((value & 0x00ff));
                if (const auto bitset = dynamic_cast<Bitset *>(m_protocol.elementMap.at(lowAdd))) {
                    bitset->setValue(l);
                    Q_EMIT updateGui(bitset->address());
                }
            }
        }
    }
}

bool ModbusCom::initializeServer()
{
    QModbusDataUnitMap reg;
    auto maxAddress = 0;

    for (const auto &el : m_protocol.elementMap) {
        if (el.first > maxAddress) {
            maxAddress = el.first;
        }
    }

    reg.insert(QModbusDataUnit::HoldingRegisters,
               {QModbusDataUnit::HoldingRegisters, 0, static_cast<quint16>(maxAddress + 1)});

    return m_modbusDevice->setMap(reg);
}
