#pragma once

#include <QSerialPort>

class Settings
{
public:
    Settings() = default;
    Settings(const Settings &) = default;
    Settings(Settings &&) = default;
    ~Settings() = default;

    Settings &operator=(const Settings &) = default;
    Settings &operator=(Settings &&) = default;

    bool operator==(const Settings &other) const;
    bool operator!=(const Settings &other) const;

    struct Tags
    {
        constexpr static const auto port_name = "PortName";
        constexpr static const auto baud_rate = "BaudRate";
        constexpr static const auto break_enabled = "BreakEnabled";
        constexpr static const auto data_bits = "DataBits";
        constexpr static const auto data_terminal_ready = "DataTerminalReady";
        constexpr static const auto flow_control = "FlowControl";
        constexpr static const auto parity = "Parity";
        constexpr static const auto request_to_send = "RequestToSend";
        constexpr static const auto stop_bits = "StopBits";
    };

    QString portName{};
    QSerialPort::BaudRate baudRate{QSerialPort::BaudRate::Baud115200};
    bool breakEnabled{false};
    QSerialPort::DataBits dataBits{QSerialPort::DataBits::Data8};
    bool dataTerminalReady{false};
    QSerialPort::FlowControl flowControl{QSerialPort::FlowControl::NoFlowControl};
    QSerialPort::Parity parity{QSerialPort::Parity::NoParity};
    bool requestToSend{false};
    QSerialPort::StopBits stopBits{QSerialPort::StopBits::OneStop};
};
