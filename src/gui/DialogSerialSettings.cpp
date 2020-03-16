#include "DialogSerialSettings.hpp"

#include "ui_DialogSerialSettings.h"

#include <QMessageBox>
#include <QMetaEnum>
#include <QSerialPort>
#include <QSerialPortInfo>

DialogSerialSettings::DialogSerialSettings(Settings *settings, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DialogSerialSettings)
    , m_settings(settings)
{
    ui->setupUi(this);

    bool portAvailable = false;
    foreach (const auto &serialPort, QSerialPortInfo::availablePorts()) {
        ui->serialPortComboBox->addItem(serialPort.portName());

        if (serialPort.portName()
            == m_settings->portName.mid(m_settings->portName.lastIndexOf('/') + 1,
                                        m_settings->portName.size())) {
            portAvailable = true;
        }
    }

    if (portAvailable) {
        ui->serialPortComboBox->setCurrentText(
            m_settings->portName.mid(m_settings->portName.lastIndexOf('/') + 1,
                                     m_settings->portName.size()));
    } else {
        ui->serialPortOverrideGroupBox->setChecked(true);
        ui->serialPortOverrideLineEdit->setText(m_settings->portName);
        serialPortOverrideBox();
    }

    QMetaEnum metaEnum = QMetaEnum::fromType<QSerialPort::BaudRate>();
    for (auto i = 0; i < metaEnum.keyCount(); ++i) {
        ui->baudRateComboBox->addItem(metaEnum.key(i));
    }
    ui->baudRateComboBox->setCurrentText(metaEnum.valueToKey(m_settings->baudRate));

    metaEnum = QMetaEnum::fromType<QSerialPort::DataBits>();
    for (auto i = 0; i < metaEnum.keyCount(); ++i) {
        ui->dataBitsComboBox->addItem(metaEnum.key(i));
    }
    ui->dataBitsComboBox->setCurrentText(metaEnum.valueToKey(m_settings->dataBits));

    metaEnum = QMetaEnum::fromType<QSerialPort::Parity>();
    for (auto i = 0; i < metaEnum.keyCount(); ++i) {
        ui->parityComboBox->addItem(metaEnum.key(i));
    }
    ui->parityComboBox->setCurrentText(metaEnum.valueToKey(m_settings->parity));

    metaEnum = QMetaEnum::fromType<QSerialPort::StopBits>();
    for (auto i = 0; i < metaEnum.keyCount(); ++i) {
        ui->stopBitsComboBox->addItem(metaEnum.key(i));
    }
    ui->stopBitsComboBox->setCurrentText(metaEnum.valueToKey(m_settings->stopBits));

    metaEnum = QMetaEnum::fromType<QSerialPort::FlowControl>();
    for (auto i = 0; i < metaEnum.keyCount(); ++i) {
        ui->flowControlComboBox->addItem(metaEnum.key(i));
    }
    ui->flowControlComboBox->setCurrentText(metaEnum.valueToKey(m_settings->flowControl));

    connect(ui->serialPortOverrideGroupBox,
            &QGroupBox::clicked,
            this,
            &DialogSerialSettings::serialPortOverrideBox);
}

DialogSerialSettings::~DialogSerialSettings()
{
    delete ui;
}

void DialogSerialSettings::serialPortOverrideBox()
{
    ui->serialPortComboBox->setEnabled(!ui->serialPortOverrideGroupBox->isChecked());
}

void DialogSerialSettings::accept()
{
    Settings s;

    if (!ui->serialPortOverrideGroupBox->isChecked()) {
        s.portName = "/dev/" + ui->serialPortComboBox->currentText();
    } else {
        s.portName = ui->serialPortOverrideLineEdit->text();
    }

    QMetaEnum metaEnum = QMetaEnum::fromType<QSerialPort::BaudRate>();
    s.baudRate = static_cast<QSerialPort::BaudRate>(
        metaEnum.keyToValue(ui->baudRateComboBox->currentText().toStdString().c_str()));

    metaEnum = QMetaEnum::fromType<QSerialPort::DataBits>();
    s.dataBits = static_cast<QSerialPort::DataBits>(
        metaEnum.keyToValue(ui->dataBitsComboBox->currentText().toStdString().c_str()));

    metaEnum = QMetaEnum::fromType<QSerialPort::Parity>();
    s.parity = static_cast<QSerialPort::Parity>(
        metaEnum.keyToValue(ui->parityComboBox->currentText().toStdString().c_str()));

    metaEnum = QMetaEnum::fromType<QSerialPort::StopBits>();
    s.stopBits = static_cast<QSerialPort::StopBits>(
        metaEnum.keyToValue(ui->stopBitsComboBox->currentText().toStdString().c_str()));

    metaEnum = QMetaEnum::fromType<QSerialPort::FlowControl>();
    s.flowControl = static_cast<QSerialPort::FlowControl>(
        metaEnum.keyToValue(ui->flowControlComboBox->currentText().toStdString().c_str()));

    if (*m_settings != s) {
        int ret = QMessageBox::warning(this,
                                       tr("Serial Settings"),
                                       tr("Settings has been modified.\n"
                                          "Do you want to save your changes?"),
                                       QMessageBox::Save | QMessageBox::Discard
                                           | QMessageBox::Cancel,
                                       QMessageBox::Save);

        switch (ret) {
        case QMessageBox::Save:
            *m_settings = s;
            break;
        case QMessageBox::Discard:
            QDialog::accept();
            break;
        case QMessageBox::Cancel:
        default:
            return;
        }
    }

    QDialog::accept();
}
