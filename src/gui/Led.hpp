#pragma once

#include <QHash>
#include <QWidget>

#include <memory>

class Bitset;
class QSvgRenderer;

class Led final : public QWidget
{
    Q_OBJECT

public:
    friend class LedRenderer;

    enum LedColor {
        Grey,
        Green,

        MaxLedColor
    };

    enum LedShape { Circle, MaxLedShape };

    enum State {
        Off,
        On,

        MaxState
    };

    explicit Led(QString description = {}, Led::State state = Led::Off, QWidget *parent = nullptr);

    [[nodiscard]] Led::State state() const;
    void setState(const Led::State &state);

    [[nodiscard]] QString description() const;
    void setDescription(const QString &description);

    [[nodiscard]] bool isInteractive();
    void setInteractive(bool value);

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
    bool m_interactive{true};

    Bitset *m_bitset{nullptr};
    size_t m_bitIndex{};

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
