#include "Led.hpp"

#include <Bitset.hpp>
#include <QApplication>
#include <QtSvg>
#include <bitset>
#include <utility>

const int spacing        = 2;
const int ledMinimumSize = 24;
const int ledMaximumSize = 32;

LedRenderer *LedRenderer::istance = nullptr;

LedRenderer::LedRenderer(QObject *parent) : QObject(parent)
{
    init();
}

LedRenderer::~LedRenderer()
{
    qDeleteAll(m_renderers);
    m_renderers.clear();
}

LedRenderer *LedRenderer::getIstance()
{
    if (!istance) {
        istance = new LedRenderer(QGuiApplication::instance());
    }
    return istance;
}

QSvgRenderer *LedRenderer::getRenderer(const Led::LedShape &shape,
                                       const Led::LedColor &color)
{
    QPair<Led::LedShape, Led::LedColor> pair(shape, color);
    return m_renderers.value(pair, nullptr);
}

void LedRenderer::init()
{
    static const QString prefix    = QString(":/resources/");
    static const QString extension = QString(".svg");
    for (int i = 0; i < Led::MaxLedShape; i++) {
        for (int j = 0; j < Led::MaxLedColor; j++) {
            auto shape = static_cast<Led::LedShape>(i);
            auto color = static_cast<Led::LedColor>(j);
            auto file  = QString("%1%2_%3%4")
                            .arg(prefix, stringifyShape(shape),
                                 stringifyColor(color), extension);
            m_renderers.insert(
                QPair<Led::LedShape, Led::LedColor>(shape, color),
                new QSvgRenderer(file, this));
        }
    }
}

QString LedRenderer::stringifyColor(const Led::LedColor &color) const
{
    QString ret = QString();
    switch (color) {
        case Led::Red:
            ret = QString("red");
            break;
        case Led::Green:
            ret = QString("green");
            break;
        case Led::Yellow:
            ret = QString("yellow");
            break;
        case Led::Grey:
            ret = QString("grey");
            break;
        case Led::Orange:
            ret = QString("orange");
            break;
        case Led::Purple:
            ret = QString("purple");
            break;
        case Led::Blue:
            ret = QString("blue");
            break;
        default:
            break;
    }
    return ret;
}

QString LedRenderer::stringifyShape(const Led::LedShape &shape) const
{
    QString ret = QString();
    switch (shape) {
        case Led::Circle:
            ret = QString("circle");
            break;
        case Led::Square:
            ret = QString("square");
            break;
        case Led::Triangle:
            ret = QString("triang");
            break;
        case Led::Rounded:
            ret = QString("round");
            break;
        default:
            break;
    }
    return ret;
}

Led::Led(QString description, QWidget *parent, const QSize &ledSize,
         State state, const Led::LedColor &onColor,
         const Led::LedColor &offColor, const Led::LedShape &shape,
         int textAligment) :
    QWidget(parent),
    m_ledSize(ledSize), m_state(state), m_onColor(onColor),
    m_offColor(offColor), m_shape(shape), m_description(std::move(description)),
    m_textAligment(textAligment), m_blinkTimer(new QTimer(this)),
    m_tag(QString())
{
    init();
}

Led::Led() :
    QWidget(nullptr), m_ledSize(QSize(30, 30)), m_blinkTimer(new QTimer(this))
{
    init();
}

Led::~Led()
{
    delete m_blinkTimer;
}

void Led::setLedSize(QSize size)
{
    m_ledSize = size;
}

void Led::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
    QSvgRenderer *renderer = LedRenderer::getIstance()->getRenderer(
        m_shape, m_state ? m_onColor : m_offColor);
    if (!renderer) {
        event->ignore();
        return;
    }

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    const auto pos = QPoint(rect().x() + spacing, rect().y() + spacing);
    const auto usefulRect =
        QRect(pos.x(), pos.y(), rect().width() - (spacing * 2),
              rect().height() - (spacing * 2));
    const auto center   = usefulRect.center();
    auto available_size = size();
    available_size.setHeight(available_size.height() -
                             (fontMetrics().height() + spacing));
    auto led_size = qMin(available_size.width(), available_size.height());
    if (led_size > ledMaximumSize)
        led_size = ledMaximumSize;
    QRect ledRect(center.x() - (led_size / 2), usefulRect.y(), led_size,
                  led_size);
    renderer->render(&painter, ledRect);
    if (!m_description.isEmpty()) {
        const auto textRect =
            QRectF(usefulRect.x(), ledRect.height() + spacing,
                   usefulRect.width(), fontMetrics().height());
        const auto desc = fontMetrics().elidedText(
            m_description, Qt::ElideMiddle, textRect.width());
        painter.drawText(textRect, m_textAligment, desc);
    }
#ifdef PAINT_BOUNDING_RECT
    painter.drawRect(rect());
#endif
}

void Led::mousePressEvent(QMouseEvent *event)
{
    QWidget::mousePressEvent(event);
    if (!m_interactive)
        return;
    toggle();
    emit clicked();
}

void Led::init()
{
    connect(m_blinkTimer, SIGNAL(timeout()), this, SLOT(toggle()));
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    checkWidgetSize();
}

void Led::checkWidgetSize()
{
    if (m_ledSize.isEmpty()) {
        // calculate minimum size
        QSize led_size = QSize(ledMinimumSize, ledMinimumSize);
        QSize text_size;
        if (!m_description.isEmpty()) {
            text_size.setWidth(fontMetrics().horizontalAdvance(m_description));
            text_size.setHeight(fontMetrics().height());
        }

        setMinimumSize(led_size.width() + text_size.width(),
                       led_size.height() + text_size.height());
    } else {
        int w = qMax(m_ledSize.width(),
                     fontMetrics().horizontalAdvance(m_description)) +
                (spacing * 2);
        int h = m_ledSize.height() + (spacing * 2);
        if (!m_description.isEmpty()) {
            h += fontMetrics().height() + spacing;
        }
        QSize currentSize(w, h);
        if (minimumSize() != currentSize) {
            setMinimumSize(currentSize);
            emit sizeChanged();
        }
    }

    update();
}

QString Led::description() const
{
    return m_description;
}

void Led::setDescription(const QString &description)
{
    QString desc = description.trimmed();
    if (m_description != desc) {
        m_description = desc;
        checkWidgetSize();
    }
}

void Led::setBlinkEnabled(bool enable, int blinkMsec)
{
    m_blink = enable;
    if (enable)
        m_blinkTimer->start(blinkMsec);
    else
        m_blinkTimer->stop();
}

bool Led::isBlinking() const
{
    return m_blink;
}

void Led::setInteractive(bool value)
{
    if (value != m_interactive)
        m_interactive = value;
}

bool Led::isInteractive()
{
    return m_interactive;
}

void Led::setTag(const QString &tag)
{
    if (tag != m_tag)
        m_tag = tag;
}

void Led::attachBitset(Bitset *bitset, size_t bitIndex)

{
    m_bitset   = bitset;
    m_bitIndex = bitIndex;
}

QString Led::tag() const
{
    return m_tag;
}

int Led::textAligment() const
{
    return m_textAligment;
}

void Led::setTextAligment(const int &textAligment)
{
    m_textAligment = textAligment;
    checkWidgetSize();
}

Led::LedShape Led::shape() const
{
    return m_shape;
}

void Led::setShape(const LedShape &shape)
{
    m_shape = shape;
    checkWidgetSize();
}

Led::State Led::state() const
{
    return m_state;
}

void Led::setState(const State &state)
{
    if (m_state != state) {
        m_state = state;
        update();
    }
}

void Led::toggle()
{
    auto bitEnabled = false;

    if (m_state == Led::On) {
        setState(Led::Off);
    } else {
        bitEnabled = true;
        setState(Led::On);
    }

    if (m_bitset) {
        m_bitset->setAt(m_bitIndex, bitEnabled);
        Q_EMIT bitsetStateChanged(m_bitset->address());
    }
}

Led::LedColor Led::color(const Led::State &state) const
{
    if (state == On)
        return m_onColor;
    return m_offColor;
}

void Led::setColor(const Led::State &state, const Led::LedColor &color)
{
    if (state == On)
        m_onColor = color;
    else
        m_offColor = color;
    checkWidgetSize();
}
