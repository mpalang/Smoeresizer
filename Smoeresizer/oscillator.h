#pragma once

class Oscillator
{
public:
    explicit Oscillator(double sampleRate = 44100.0);

    void setFrequency(double freqHz);
    double nextSample(); // returns value in [-1, 1]

private:
    double m_sampleRate;
    double m_frequency = 440.0;
    double m_phase = 0.0;
};
