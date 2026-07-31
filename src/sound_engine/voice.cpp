#include "voice.h"
#include <algorithm>

Voice::Voice(double sampleRate)
    : m_oscillator(sampleRate)
{
}

void Voice::noteOn(double frequency)
{
    m_frequency = frequency;
    m_oscillator.setFrequency(frequency);
    m_active = true;
    m_target = 1.0f;
    m_step = 1.0f / (0.005f * 44100.0f);   // 5ms ramp
}

void Voice::noteOff()
{   
    m_target = 0.0f;
    m_step = 1.0f / (0.005f * 44100.0f);
}

bool Voice::isActive() const
{
    return m_active;
}

double Voice::frequency() const
{
    return m_frequency;
}

void Voice::addTo(float* buffer, int numFrames)
{
    if (!m_active)
        return;

    for (int i = 0; i < numFrames; ++i) {
        if (m_gain < m_target)
            m_gain = std::min(m_gain + m_step, m_target);
        else if (m_gain > m_target)
            m_gain = std::max(m_gain - m_step, m_target);

        buffer[i] += static_cast<float>(m_oscillator.nextSample()) * m_gain;
    }

    if (m_target == 0.0f && m_gain == 0.0f)
        m_active = false;   // fully faded out, voice is free again
}