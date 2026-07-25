#include "audiosource.h"
#include <QDebug>

AudioSource::AudioSource(QObject* parent)
    : QIODevice(parent), m_oscillator(44100.0)
{
    m_oscillator.setFrequency(440.0); // A4, change to whatever xHz you want
}

void AudioSource::start()
{
    bool ok = open(QIODevice::ReadOnly);
    qDebug() << "AudioSource::start() open() returned:" << ok;
}

void AudioSource::stop()
{
    close();
}

qint64 AudioSource::readData(char* data, qint64 maxlen)
{
    static int callCount = 0;
    qint64 numSamples = maxlen / static_cast<qint64>(sizeof(qint16));
    qint16* out = reinterpret_cast<qint16*>(data);

    for (qint64 i = 0; i < numSamples; ++i) {
        double sample = m_oscillator.nextSample();
        out[i] = static_cast<qint16>(sample * 32767 * 0.3);
    }

    if (++callCount % 50 == 0)
        qDebug() << "readData called" << callCount << "times, last sample:" << out[0];

    return numSamples * static_cast<qint64>(sizeof(qint16));
}

qint64 AudioSource::writeData(const char*, qint64)
{
    return -1; // playback-only device, writing not supported
}

qint64 AudioSource::bytesAvailable() const
{
    return std::numeric_limits<qint64>::max() / 2; // "infinite" stream, halved to avoid overflow in Qt's internal math
}