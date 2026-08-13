#pragma once
#include <string>

class Oscillator
{
public:
    explicit Oscillator(double sampleRate = 44100.0);

    enum class Waveforms { Sine, Square, Sawtooth, Triangle };

    void setWaveform(Waveforms w);
    Waveforms waveform() const;

    void setFrequency(double freqHz);
    void setOctave(int octave);
    void setDetune(int detune);
    void reset() { m_phase = 0.0; }

    double nextSample(); // returns value in [-1, 1]

private:
    double m_sampleRate;
    double m_frequency = 440.0;
    double m_phase = 0.0;
    double m_detune = 0;
    int m_octave = 0;

    Waveforms m_waveform = Waveforms::Sine;
};
