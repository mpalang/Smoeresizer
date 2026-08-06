#include "synthengine.h"
#include <algorithm>
#include <cmath>

SynthEngine::SynthEngine(double sampleRate, int maxVoices, size_t numOscillators)
    : m_voices(maxVoices, Voice(sampleRate, numOscillators)),
    m_settings(numOscillators)
{
}

void SynthEngine::noteOn(double frequency)
{
    for (auto& v : m_voices) {
        if (!v.isActive()) {
            v.noteOn(frequency, m_settings);
            return;
        }
    }
    // all voices busy: silently drop the note for now
}

void SynthEngine::noteOff(double frequency)
{
    for (auto& v : m_voices) {
        if (v.isActive() && std::abs(v.frequency() - frequency) < 0.001) {
            v.noteOff();
            return;
        }
    }
}

void SynthEngine::render(std::vector<float>& buffer)
{
    std::fill(buffer.begin(), buffer.end(), 0.0f);

    for (auto& v : m_voices)
        v.addTo(buffer.data(), static_cast<int>(buffer.size()), m_settings);
}

int SynthEngine::activeVoices() const
{
    int n = 0;
    for (const auto& v : m_voices)
        if (v.isActive())
            ++n;
    return n;
}

void SynthEngine::setOscillator(size_t index, const OscillatorSettings& s)
{
    if (index < m_settings.size())
        m_settings[index] = s;
}