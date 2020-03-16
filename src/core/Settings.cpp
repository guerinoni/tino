#include "Settings.hpp"

bool Settings::operator==(const Settings &other) const
{
    return portName == other.portName && baudRate == other.baudRate
           && breakEnabled == other.breakEnabled && dataBits == other.dataBits
           && dataTerminalReady == other.dataTerminalReady && stopBits == other.stopBits
           && flowControl == other.flowControl && requestToSend == other.requestToSend;
}

bool Settings::operator!=(const Settings &other) const
{
    return !(*this == other);
}
