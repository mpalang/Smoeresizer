#pragma once
#include "oscillator.h"

class Voice
{
public:
    explicit Voice(double sampleRate = 44100.0);

    void noteOn(double frequency);
    void noteOff();
    bool isActive() const;
    double frequency() const;

    void addTo(float* buffer, int numFrames); // accumulates into buffer

private:
    Oscillator m_oscillator;
    bool m_active = false;
    double m_frequency = 0.0;
    float m_gain = 0.0f;
    float m_target = 0.0f;
    float m_step = 0.0f;
};