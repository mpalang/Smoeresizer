#pragma once
#include <vector>
#include "voice.h"
#include "oscillator.h"

class SynthEngine
{
public:
    explicit SynthEngine(double sampleRate = 44100.0, 
                            int maxVoices = 8,
                            size_t numOscillators = 2);

    void noteOn(double frequency);
    void noteOff(double frequency);

    void setOscillator(size_t index, const OscillatorSettings& s);

    int activeVoices() const;

    // fills buffer with the mix of all active voices
    void render(std::vector<float>& buffer);

private:
    std::vector<Voice> m_voices;
    std::vector<OscillatorSettings> m_settings;
};