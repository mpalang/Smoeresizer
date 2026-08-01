#include "oscilloscope.h"

#include <QPainter>
#include <QPainterPath>
#include <QTimer>

Oscilloscope::Oscilloscope(QWidget* parent)
    : QWidget(parent)
{
    setFixedHeight(120);
    m_capture.resize(m_displayLength * 2, 0.0f);   // 2x gives room to search

    auto* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, QOverload<>::of(&QWidget::update));
    timer->start(33);   // ~30 fps
}

void Oscilloscope::pushSamples(const float* data, int count)
{
    QMutexLocker lock(&m_mutex);
    const int n = std::min(count, static_cast<int>(m_capture.size()));
    std::rotate(m_capture.begin(), m_capture.begin() + n, m_capture.end());
    std::copy(data, data + n, m_capture.end() - n);
}

void Oscilloscope::paintEvent(QPaintEvent*)
{
    std::vector<float> copy;
    {
        QMutexLocker lock(&m_mutex);
        copy = m_capture;
    }

    QPainter p(this);
    p.fillRect(rect(), Qt::black);
    p.setPen(QPen(Qt::green, 1));

    const int w = width();
    const int h = height();
    const float mid = h / 2.0f;

    // search the first half for a rising zero-crossing
    int trigger = 0;
    const int searchEnd = static_cast<int>(copy.size()) - m_displayLength;
    for (int i = 1; i < searchEnd; ++i) {
        if (copy[i - 1] <= 0.0f && copy[i] > 0.0f) {
            trigger = i;
            break;
        }
    }

    // for normalization
    float peak = 0.0f;
    for (int x = 0; x < w; ++x) {
        const int idx = trigger + x * m_displayLength / w;
        peak = std::max(peak, std::abs(copy[idx]));
    }
    const float scale = (peak > 0.001f) ? (0.9f / peak) : 1.0f;

    QPainterPath path;
    for (int x = 0; x < w; ++x) {
        const int idx = trigger + x * m_displayLength / w;
        const float y = mid - copy[idx] * scale * mid;
        if (x == 0)
            path.moveTo(x, y);
        else
            path.lineTo(x, y);
    }

    p.drawPath(path);
}