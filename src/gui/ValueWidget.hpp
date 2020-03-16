#pragma once

#include <QWidget>

class Element;
class QLabel;
class QSpinBox;

class ValueWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ValueWidget(Element *element,
                         int16_t value,
                         QString description = {},
                         QWidget *parent = nullptr);

    void updateValue(int16_t val);

signals:
    void valueChanged(int address);

private:
    QString m_description{""};
    int16_t m_defaultValue{0};
    int16_t m_value{0};
    QLabel *m_decValueLabel{nullptr};
    QLabel *m_hexValueLabel{nullptr};
    QSpinBox *m_valueSpinBox{nullptr};
    Element *m_element{nullptr};

    void init();
    void checkWidgetSize();
    void update();
};
