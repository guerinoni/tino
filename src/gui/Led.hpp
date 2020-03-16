#pragma once

#include <memory>
#include <QHash>
#include <QWidget>

class Bitset;
class QSvgRenderer;

class Led : public QWidget
{
    Q_OBJECT

public:
    friend class LedRenderer;

    enum LedColor {
        Red,
        Green,
        Yellow,
        Grey,
        Orange,
        Purple,
        Blue,

        MaxLedColor
    };

    enum LedShape {
        Circle,
        Square,
        Triangle,
        Rounded,

        MaxLedShape
    };

    enum State {
        Off,
        On,

        MaxState
    };

    Led(QString description = QString(),
        QWidget *parent = nullptr,
        const QSize &ledSize = QSize(30, 30),
        Led::State state = Led::Off,
        const Led::LedColor &onColor = Led::Green,
        const Led::LedColor &offColor = Led::Grey,
        const Led::LedShape &shape = Led::Circle,
        int textAligment = Qt::AlignCenter);
    Led();
    ~Led() override;

    [[nodiscard]] Led::State state() const;
    void setState(const Led::State &state);

    [[nodiscard]] LedColor color(const State &state) const;
    void setColor(const State &state, const LedColor &color);

    [[nodiscard]] LedShape shape() const;
    void setShape(const LedShape &shape);

    void setLedSize(QSize size);

    [[nodiscard]] int textAligment() const;
    void setTextAligment(const int &textAligment);

    [[nodiscard]] QString description() const;
    void setDescription(const QString &description);

    [[nodiscard]] bool isBlinking() const;
    void setBlinkEnabled(bool enable, int blinkMsec = 2000);

    [[nodiscard]] bool isInteractive();
    void setInteractive(bool value);

    [[nodiscard]] QString tag() const;
    void setTag(const QString &tag);

    void attachBitset(Bitset *bitset, size_t bitIndex);

public slots:
    void toggle();

signals:
    void sizeChanged();
    void clicked();
    void bitsetStateChanged(int address);

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

private:
    QSize m_ledSize;
    State m_state{Led::Off};
    LedColor m_onColor{Led::Green};
    LedColor m_offColor{Led::Grey};
    LedShape m_shape{Led::Circle};
    QString m_description{};
    int m_textAligment{Qt::AlignCenter};
    bool m_blink{false};
    QTimer *m_blinkTimer;
    bool m_interactive{true};
    QString m_tag{};

    Bitset *m_bitset{nullptr};
    size_t m_bitIndex{};

    void init();
    void checkWidgetSize();
};

class LedRenderer : public QObject
{
    Q_OBJECT

public:
    static LedRenderer *getIstance();

    QSvgRenderer *getRenderer(const Led::LedShape &shape, const Led::LedColor &color);

private:
    QHash<QPair<Led::LedShape, Led::LedColor>, QSvgRenderer *> m_renderers;
    static LedRenderer *istance;

    explicit LedRenderer(QObject *parent = nullptr);
    ~LedRenderer() override;

    void init();
    [[nodiscard]] QString stringifyColor(const Led::LedColor &color) const;
    [[nodiscard]] QString stringifyShape(const Led::LedShape &shape) const;
};
