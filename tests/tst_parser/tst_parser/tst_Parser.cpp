#include <Bitset.hpp>
#include <Byte.hpp>
#include <ConfigParser.hpp>
#include <Word.hpp>
#include <QDir>
#include <QtTest>

#define STRINGIFY_INTERNAL(x) #x
#define STRINGIFY(x) STRINGIFY_INTERNAL(x)

class tst_Parser : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();

    void throwIfNotExists();
    void withoutSettings();
    void normalSettings();
    void parseBitset();
    void parseByte();
    void parseWord();

private:
    QString path_{};
    ConfigParser cp_;
};

void tst_Parser::initTestCase()
{
    path_ = STRINGIFY(TINO_PROJECT_DIR) + QStringLiteral("/tests/files/");
}

void tst_Parser::throwIfNotExists()
{
    QVERIFY_EXCEPTION_THROWN(cp_.parse(""), std::logic_error);
}

void tst_Parser::withoutSettings()
{
    auto config = cp_.parse(path_ + "empty.json");
    QVERIFY((config == Configuration{Settings{}, Protocol{}}));
}

void tst_Parser::normalSettings()
{
    Settings right_settings;
    right_settings.portName = "/dev/ttymxc1";
    right_settings.baudRate = QSerialPort::BaudRate::Baud115200;
    right_settings.breakEnabled = false;
    right_settings.dataBits = QSerialPort::DataBits::Data8;
    right_settings.dataTerminalReady = false;
    right_settings.flowControl = QSerialPort::FlowControl::NoFlowControl;
    right_settings.parity = QSerialPort::Parity::NoParity;
    right_settings.requestToSend = false;
    right_settings.stopBits = QSerialPort::StopBits::OneStop;

    auto config = cp_.parse(path_ + "protocol.json");
    QVERIFY(config.settings == right_settings);
}

void tst_Parser::parseBitset()
{
    const auto config = cp_.parse(path_ + "protocol.json");
    const auto &p = config.protocol;
    QVERIFY(!p.blocks.empty());
    QCOMPARE(p.blocks.front().description, "");
    QCOMPARE(p.blocks.front().elements.size(), size_t(5));
    auto b = dynamic_cast<Bitset *>(p.blocks.front().elements.front().get());
    QVERIFY(b != Q_NULLPTR);
    QCOMPARE(b->address(), 262);
    QCOMPARE(b->description(), "BitsetDescription");
    QCOMPARE(b->descriptions().size(), 8);
    QCOMPARE(p.elementMap.at(b->address())->description(), b->description());
}

void tst_Parser::parseByte()
{
    const auto config = cp_.parse(path_ + "protocol.json");
    const auto &p = config.protocol;
    QVERIFY(!p.blocks.empty());
    QCOMPARE(p.blocks.size(), std::size_t(1));
    const auto b = p.blocks.back();
    QCOMPARE(b.description, "");
    QCOMPARE(b.category, "Command");
    QCOMPARE(b.address, 0x0106);
    QCOMPARE(b.elements.size(), std::size_t(5));
    auto byte = b.elements.at(2);
    QCOMPARE(byte->name(), "UByte");
    auto v = byte->type() == Element::Type::SByte ? byte->sValue() : byte->uValue();
    QCOMPARE(v, 0x85);
    QCOMPARE(byte->address(), 264);
    QCOMPARE(byte->description(), "UByteDescr");
}

void tst_Parser::parseWord()
{
    const auto config = cp_.parse(path_ + "protocol.json");
    const auto &p = config.protocol;
    QVERIFY(!p.blocks.empty());
    QCOMPARE(p.blocks.front().description, "");
    QCOMPARE(p.blocks.front().elements.size(), size_t(5));
    const auto w = p.blocks.back();
    QCOMPARE(w.description, "");
    QCOMPARE(w.category, "Command");
    QCOMPARE(w.address, 0x0106);
    QCOMPARE(w.elements.size(), std::size_t(5));
    auto word = w.elements.back();
    QCOMPARE(word->name(), "UWord");
    auto v = word->type() == Element::Type::SWord ? word->sValue() : word->uValue();
    QCOMPARE(v, 0x85);
    QCOMPARE(word->address(), 266);
    QCOMPARE(word->description(), "UWordDescr");
}

QTEST_GUILESS_MAIN(tst_Parser)

#include "tst_Parser.moc"
