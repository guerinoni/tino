#pragma once

#include <Protocol.hpp>
#include <Settings.hpp>

class Bitset;
class UByte;
class SByte;
class UWord;
class SWord;

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
    struct Tags {
        constexpr static const auto settings   = "Settings";
        constexpr static const auto serialPort = "SerialPort";
        constexpr static const auto protocol   = "CommunicationProtocol";

        constexpr static const auto blocks   = "Blocks";
        constexpr static const auto groups   = "Groups";
        constexpr static const auto category = "Category";

        static constexpr auto type   = "Type";
        static constexpr auto bitset = "Bitset";
        static constexpr auto uByte  = "UByte";
        static constexpr auto sByte  = "SByte";
        static constexpr auto uWord  = "UWord";
        static constexpr auto sWord  = "SWord";

        static constexpr auto bytes = "Bytes";
        static constexpr auto bits  = "Bits";

        static constexpr auto name         = "Name";
        static constexpr auto description  = "Description";
        static constexpr auto defaultValue = "DefaultValue";
        static constexpr auto address      = "Address";
        static constexpr auto offset       = "Offset";
    };

    [[nodiscard]] Settings readSettings(const QJsonObject &obj) const noexcept;
    [[nodiscard]] Protocol readBlocks(const QJsonObject &obj) const noexcept;

    std::unique_ptr<Bitset> makeBitset(const QJsonObject &obj,
                                       const Block &b = Block()) const;
    std::unique_ptr<UByte> makeUByte(const QJsonObject &obj,
                                     const Block &b = Block()) const;
    std::unique_ptr<SByte> makeSByte(const QJsonObject &obj,
                                     const Block &b = Block()) const;
    std::unique_ptr<UWord> makeUWord(const QJsonObject &obj,
                                     const Block &b = Block()) const;
    std::unique_ptr<SWord> makeSWord(const QJsonObject &obj,
                                     const Block &b = Block()) const;
};
