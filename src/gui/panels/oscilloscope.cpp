#include "oscilloscope.h"

#include <QPainter>
#include <QPainterPath>
#include <QTimer>
#include <algorithm>
#include <cmath>

#include "fft.h"

Oscilloscope::Oscilloscope(QWidget* parent)
    : QWidget(parent)
{
    setFixedHeight(120);
    m_capture.resize(m_displayLength * 2, 0.0f);   // 2x gives room to search

    auto* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, QOverload<>::of(&QWidget::update));
    timer->start(33);   // ~30 fps
}

void Oscilloscope::setMode(Mode mode)
{
    m_mode = mode;
    update();
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
    p.setRenderHint(QPainter::Antialiasing);

    if (m_mode == Mode::Waveform)
        paintWaveform(p, copy);
    else
        paintSpectrum(p, copy);

}


void Oscilloscope::paintWaveform(QPainter& p, const std::vector<float>& samples)
{
    p.setPen(QPen(Qt::green, 1));

    const int w = width();
    const int h = height();
    const float mid = h / 2.0f;

    // search the first half for a rising zero-crossing
    int trigger = 0;
    const int searchEnd = static_cast<int>(samples.size()) - m_displayLength;
    for (int i = 1; i < searchEnd; ++i) {
        if (samples[i - 1] <= 0.0f && samples[i] > 0.0f) {
            trigger = i;
            break;
        }
    }

    // for normalization
    float peak = 0.0f;
    for (int x = 0; x < w; ++x) {
        const int idx = trigger + x * m_displayLength / w;
        peak = std::max(peak, std::abs(samples[idx]));
    }
    const float scale = (peak > 0.001f) ? (0.9f / peak) : 1.0f;

    QPainterPath path;
    for (int x = 0; x < w; ++x) {
        const int idx = trigger + x * m_displayLength / w;
        const float y = mid - samples[idx] * scale * mid;
        if (x == 0)
            path.moveTo(x, y);
        else
            path.lineTo(x, y);
    }

    p.drawPath(path);
}


void Oscilloscope::paintSpectrum(QPainter& p, const std::vector<float>& samples)
{
    // FFT wants a power of two; take the newest m_displayLength samples
    const std::vector<float> block(samples.end() - m_displayLength, samples.end());
    const std::vector<float> db = FFT::magnitudeDb(block);

    const float sampleRate = 44100.0f;
    const float binHz = sampleRate / static_cast<float>(m_displayLength);

    const float fMin = 20.0f;
    const float fMax = sampleRate / 2.0f;
    const float logMin = std::log10(fMin);
    const float logSpan = std::log10(fMax) - logMin;

    const float dbFloor = -80.0f;
    const int w = width();
    const int h = height();

    p.setPen(QPen(Qt::green, 1));

    QPainterPath path;
    bool started = false;

    for (size_t k = 1; k < db.size(); ++k) {
        const float freq = static_cast<float>(k) * binHz;
        if (freq < fMin)
            continue;

        const float x = (std::log10(freq) - logMin) / logSpan * w;
        const float norm = std::clamp((db[k] - dbFloor) / -dbFloor, 0.0f, 1.0f);
        const float y = h - norm * h;

        if (!started) { path.moveTo(x, y); started = true; }
        else          path.lineTo(x, y);
    }

    p.drawPath(path);
}