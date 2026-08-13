#include "voice.h"
#include <algorithm>
#include <cmath>

Voice::Voice(double sampleRate, size_t numOscillators)
    : m_oscillators(numOscillators, Oscillator(sampleRate)),
      m_sampleRate(sampleRate)
{
}

void Voice::noteOn(double frequency, const std::vector<OscillatorSettings>& settings)
{
    m_frequency = frequency;
    for (size_t i = 0; i < m_oscillators.size() && i < settings.size(); ++i){
        m_oscillators[i].reset();
        m_oscillators[i].setFrequency(frequency);
        m_oscillators[i].setOctave(settings[i].octave);
        m_oscillators[i].setDetune(settings[i].detune);
    }


    m_active = true;
    m_target = 1.0f;
    m_step = 1.0f / (0.005f * static_cast<float>(m_sampleRate));
}

void Voice::noteOff()
{   
    m_target = 0.0f;
    m_step = 1.0f / (0.001f * static_cast<float>(m_sampleRate));
}

void Voice::addTo(float* buffer, int numFrames, const std::vector<OscillatorSettings>& settings)
{
    if (!m_active)
        return;

    const size_t n = std::min(m_oscillators.size(), settings.size());
    if (n==0)
        return;
    
    const float norm = 1.0f / static_cast<float>(n);
    
    for (size_t i = 0; i < n; ++i) {
        m_oscillators[i].setWaveform(settings[i].waveform);
        m_oscillators[i].setFrequency(m_frequency * std::pow(2.0, settings[i].octave));
    }

    for (int s = 0; s < numFrames; ++s) {
        if (m_gain < m_target)
            m_gain = std::min(m_gain + m_step, m_target);
        else if (m_gain > m_target)
            m_gain = std::max(m_gain - m_step, m_target);
        
        float mixed = 0.0f;
        for (size_t i = 0; i < n; ++i)
            mixed += static_cast<float>(m_oscillators[i].nextSample()) * settings[i].amplitude;

        buffer[s] += mixed * norm * m_gain;
    }

    if (m_target == 0.0f && m_gain == 0.0f)
        m_active = false;   // fully faded out, voice is free again
}