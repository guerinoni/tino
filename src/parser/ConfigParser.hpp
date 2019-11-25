#pragma once

#include <Protocol.hpp>
#include <QString>
#include <Settings.hpp>

class QJsonObject;
class QJsonArray;

class Configuration
{
  public:
    Configuration() = default;
    explicit Configuration(Settings &&set, Protocol &&prot);
    Configuration(const Configuration &) = default;
    Configuration(Configuration &&)      = default;
    ~Configuration()                     = default;

    Configuration &operator=(const Configuration &) = default;
    Configuration &operator=(Configuration &&) = default;

    bool operator==(const Configuration &other) const;

    Settings settings;
    Protocol protocol;
};

class ConfigParser
{
  public:
    Configuration parse(const QString &filename);

  private:
    [[nodiscard]] Settings read_settings(const QJsonObject &obj) const noexcept;
    [[nodiscard]] Protocol read_blocks(const QJsonObject &obj) const noexcept;

    struct Tags {
        constexpr static const auto settings     = "SerialPortSettings";
        constexpr static const auto protocol     = "CommunicationProtocol";
        constexpr static const auto blocks       = "Blocks";
        constexpr static const auto groups       = "Groups";
        constexpr static const auto description  = "Description";
        constexpr static const auto type         = "Type";
        constexpr static const auto bitsarray    = "BitsArray";
        constexpr static const auto address      = "Address";
        constexpr static const auto bit          = "Bit";
        constexpr static const auto defaultValue = "DefaultValue";
    };
};
