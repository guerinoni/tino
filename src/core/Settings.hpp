#pragma once

#include <iostream>

namespace core
{
struct Settings {
    Settings()  = default;
    ~Settings() = default;
    bool operator==(const Settings &other) const;

    std::string portName;
    int Parity;
    int BaudRate;
    int DataBits;
    int StopBits;
    int ServerAddress;
    int refreshTime;
};
} // namespace core
