#pragma once

#include <iostream>

namespace connector
{
struct Settings {
    Settings()  = default;
    ~Settings() = default;
    bool operator==(const connector::Settings &other) const;

    std::string portName;
    int Parity;
    int BaudRate;
    int DataBits;
    int StopBits;
    int ServerAddress;
    int refreshTime;
};
} // namespace connector
