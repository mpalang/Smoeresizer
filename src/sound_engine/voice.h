#pragma once
#include <vector>
#include "oscillatorsettings.h"

class Voice
{
public:
    explicit Voice(double sampleRate = 44100.0, size_t numOscillators = 2);

    void noteOn(double frequency, const std::vector<OscillatorSettings>& settings);
    void noteOff();
    bool isActive() const {return m_active;}
    double frequency() const {return m_frequency;}

    void addTo(float* buffer, int numFrames, const std::vector<OscillatorSettings>& settings); // accumulates into buffer
    
private:
    std::vector<Oscillator> m_oscillators;

    bool m_active = false;
    double m_frequency = 0.0;
    double m_sampleRate;
    
    float m_gain = 0.0f;
    float m_target = 0.0f;
    float m_step = 0.0f;
};