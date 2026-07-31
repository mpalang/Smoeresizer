#pragma once
#include <vector>
#include "voice.h"

class SynthEngine
{
public:
    explicit SynthEngine(double sampleRate = 44100.0, int maxVoices = 8);

    void noteOn(double frequency);
    void noteOff(double frequency);

    // fills buffer with the mix of all active voices
    void render(std::vector<float>& buffer);

private:
    std::vector<Voice> m_voices;
};