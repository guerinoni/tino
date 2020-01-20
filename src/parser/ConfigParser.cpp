#include "ConfigParser.hpp"

#include <Bitset.hpp>
#include <Byte.hpp>
#include <QDebug>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <Word.hpp>

static constexpr int HexBase = 16;

Configuration::Configuration(Settings &&set, Protocol &&prot) :
    settings{ set }, protocol{ std::move(prot) }
{
}

bool Configuration::operator==(const Configuration &other) const
{
    return settings == other.settings && protocol == other.protocol;
}

Configuration ConfigParser::parse(const QString &filename)
{
    QFile file{ filename };
    if (!file.exists()) {
        throw std::logic_error("file not exists");
    }

    if (!file.open(QIODevice::ReadOnly)) {
        throw std::logic_error("can't open file");
    }

    QJsonParseError error{};
    const auto content = file.readAll();
    auto doc           = QJsonDocument::fromJson(content, &error);
    if (error.error != QJsonParseError::NoError) {
        throw std::logic_error("error parsing json " +
                               std::to_string(error.error));
    }

    const auto obj = doc.object();
    const auto serial =
        obj.find(Tags::settings)->toObject().find(Tags::serialPort)->toObject();
    const auto protocol = obj.find(Tags::protocol)->toObject();

    if (serial.isEmpty() && protocol.isEmpty()) {
        return {};
    }

    return Configuration{ readSettings(serial), readBlocks(protocol) };
}

Settings ConfigParser::readSettings(const QJsonObject &obj) const noexcept
{
    Settings s;

    s.portName = obj[Settings::Tags::port_name].toString(s.portName);

    s.baudRate = static_cast<QSerialPort::BaudRate>(
        obj[Settings::Tags::baud_rate].toInt(s.baudRate));

    s.breakEnabled = obj[Settings::Tags::break_enabled].toBool(s.breakEnabled);

    s.dataBits = static_cast<QSerialPort::DataBits>(
        obj[Settings::Tags::data_bits].toInt(s.dataBits));

    s.dataTerminalReady =
        obj[Settings::Tags::data_terminal_ready].toBool(s.dataTerminalReady);

    s.flowControl = static_cast<QSerialPort::FlowControl>(
        obj[Settings::Tags::flow_control].toInt(s.flowControl));

    s.requestToSend =
        obj[Settings::Tags::request_to_send].toBool(s.requestToSend);

    s.stopBits = static_cast<QSerialPort::StopBits>(
        obj[Settings::Tags::stop_bits].toInt(s.stopBits));

    return s;
}

Protocol ConfigParser::readBlocks(const QJsonObject &obj) const noexcept
{
    Protocol ret;
    const auto array = obj.find(Tags::blocks)->toArray();
    if (array.isEmpty()) {
        return ret;
    }

    foreach (auto v, array) {
        Block blk;
        const auto block = v.toObject();
        blk.description  = block.find(Tags::description)->toString();
        blk.category     = block.find(Tags::category)->toString();
        blk.address =
            block.find(Tags::address)->toString().toInt(Q_NULLPTR, HexBase);
        const auto groups = block.find(Tags::groups)->toArray();
        foreach (auto g, groups) {
            auto type = g.toObject().find(Tags::type)->toString();
            std::unique_ptr<Element> element;
            if (type == Tags::bitset) {
                element = makeBitset(g.toObject(), blk);
            } else if (type == Tags::uByte) {
                element = makeUByte(g.toObject(), blk);
            } else if (type == Tags::sByte) {
                element = makeSByte(g.toObject(), blk);
            } else if (type == Tags::uWord) {
                element = makeUWord(g.toObject(), blk);
            } else if (type == Tags::sWord) {
                element = makeSWord(g.toObject(), blk);
            } else {
                qWarning() << "tag not handled";
                continue;
            }
            blk.elements.emplace_back(std::move(element));
        }
        ret.blocks.emplace_back(std::move(blk));
    }

    for (const auto &b : ret.blocks) {
        for (const auto &el : b.elements) {
            ret.elementMap.insert({ el->address(), el.get() });
        }
    }

    return ret;
}

std::unique_ptr<Bitset> ConfigParser::makeBitset(const QJsonObject &obj,
                                                 const Block &b) const
{
    auto name        = obj.find(Tags::name)->toString();
    auto description = obj.find(Tags::description)->toString();
    auto address =
        obj.find(Tags::address)->toString().toInt(Q_NULLPTR, HexBase);
    if (address == 0) {
        address = b.address;
        address += obj.find(Tags::offset)->toString().toInt(Q_NULLPTR, HexBase);
    }
    auto element    = std::make_unique<Bitset>(name, description, address);
    auto bits       = obj.find(Tags::bits)->toArray();
    auto bitset     = dynamic_cast<Bitset *>(element.get());
    const auto size = static_cast<size_t>(bits.size());
    for (size_t i = 0; i < size; ++i) {
        auto obj = bits[i].toObject();
        auto d   = obj.find(Tags::description)->toString();
        auto n   = obj.find(Tags::name)->toString();
        auto val = obj.find(Tags::defaultValue)->toBool();
        bitset->setAt(i, val, n, d);
    }

    return element;
}

std::unique_ptr<UByte> ConfigParser::makeUByte(const QJsonObject &obj,
                                               const Block &b) const
{
    auto name        = obj.find(Tags::name)->toString();
    auto description = obj.find(Tags::description)->toString();
    auto address =
        obj.find(Tags::address)->toString().toInt(Q_NULLPTR, HexBase);
    if (address == 0) {
        address = b.address;
        address += obj.find(Tags::offset)->toString().toInt(Q_NULLPTR, HexBase);
    }

    auto element = std::make_unique<UByte>(name, description, address);
    auto val     = static_cast<uint16_t>(
        obj.find(Tags::defaultValue)->toString().toUInt(Q_NULLPTR, HexBase));
    element->setValue(val);
    return element;
}

std::unique_ptr<SByte> ConfigParser::makeSByte(const QJsonObject &obj,
                                               const Block &b) const
{
    auto name        = obj.find(Tags::name)->toString();
    auto description = obj.find(Tags::description)->toString();
    auto address =
        obj.find(Tags::address)->toString().toInt(Q_NULLPTR, HexBase);
    if (address == 0) {
        address = b.address;
        address += obj.find(Tags::offset)->toString().toInt(Q_NULLPTR, HexBase);
    }

    auto element = std::make_unique<SByte>(name, description, address);
    auto val     = static_cast<int16_t>(
        obj.find(Tags::defaultValue)->toString().toInt(Q_NULLPTR, HexBase));
    element->setValue(val);
    return element;
}

std::unique_ptr<UWord> ConfigParser::makeUWord(const QJsonObject &obj,
                                               const Block &b) const
{
    auto name        = obj.find(Tags::name)->toString();
    auto description = obj.find(Tags::description)->toString();
    auto address =
        obj.find(Tags::address)->toString().toInt(Q_NULLPTR, HexBase);
    if (address == 0) {
        address = b.address;
        address += obj.find(Tags::offset)->toString().toInt(Q_NULLPTR, HexBase);
    }

    auto element = std::make_unique<UWord>(name, description, address);
    auto val     = static_cast<uint16_t>(
        obj.find(Tags::defaultValue)->toString().toUInt(Q_NULLPTR, HexBase));
    element->setValue(val);
    return element;
}

std::unique_ptr<SWord> ConfigParser::makeSWord(const QJsonObject &obj,
                                               const Block &b) const
{
    auto name        = obj.find(Tags::name)->toString();
    auto description = obj.find(Tags::description)->toString();
    auto address =
        obj.find(Tags::address)->toString().toInt(Q_NULLPTR, HexBase);
    if (address == 0) {
        address = b.address;
        address += obj.find(Tags::offset)->toString().toInt(Q_NULLPTR, HexBase);
    }

    auto element = std::make_unique<SWord>(name, description, address);
    auto val     = static_cast<int16_t>(
        obj.find(Tags::defaultValue)->toString().toInt(Q_NULLPTR, HexBase));
    element->setValue(val);
    return element;
}
