#include "audiosource.h"
#include <algorithm>
#include <limits>

AudioSource::AudioSource(QObject* parent)
    : QIODevice(parent)
{
}

void AudioSource::start()
{
    open(QIODevice::ReadOnly);
}

void AudioSource::stop()
{
    close();
}

void AudioSource::noteOn(double frequency)
{
    m_engine.noteOn(frequency);
}

void AudioSource::noteOff(double frequency)
{
    m_engine.noteOff(frequency);
}

qint64 AudioSource::readData(char* data, qint64 maxlen)
{
    const int numFrames = static_cast<int>(maxlen / sizeof(qint16));
    if (numFrames <= 0)
        return 0;

    if (static_cast<int>(m_buffer.size()) != numFrames)
        m_buffer.resize(numFrames);

    m_engine.render(m_buffer);

    if (m_view)
        m_view->pushSamples(m_buffer.data(), numFrames);

    // ---- effects go here: operate on m_buffer before conversion ----

    qint16* out = reinterpret_cast<qint16*>(data);
    for (int i = 0; i < numFrames; ++i) {
        float s = std::clamp(m_buffer[i] * 0.3f, -1.0f, 1.0f);
        out[i] = static_cast<qint16>(s * 32767.0f);
    }

    return numFrames * static_cast<qint64>(sizeof(qint16));
}

qint64 AudioSource::writeData(const char*, qint64)
{
    return -1; // playback-only device, writing not supported
}

qint64 AudioSource::bytesAvailable() const
{
    return std::numeric_limits<qint64>::max() / 2; // "infinite" stream, halved to avoid overflow in Qt's internal math
}