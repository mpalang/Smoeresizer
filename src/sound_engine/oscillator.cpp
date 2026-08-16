#include "oscillator.h"
#include <cmath>


namespace {
    constexpr double kPi = 3.1415926535897932384626433; // avoid M_PI (not standard on MSVC)
}


Oscillator::Oscillator(double sampleRate) : m_sampleRate(sampleRate)
{
}

void Oscillator::setFrequency(double freqHz)
{
    m_frequency = freqHz;
}
void Oscillator::setWaveform(Waveforms w)
{
    m_waveform = w;
}

void Oscillator::setAmplitude(int amplitude)
{
    m_amplitude = amplitude;
}

void Oscillator::setOctave(int octave)
{
    m_octave = octave;
}

void Oscillator::setDetune(int detune)
{
    m_detune = detune;
}

double Oscillator::nextSample()
{   
    double sample = 0.0;

    switch(m_waveform){
        case Waveforms::Sine:
            sample = std::sin(m_phase);
            break;

        case Waveforms::Square:
            sample = (m_phase < kPi) ? 1.0 : -1.0;
            break;
        
        case Waveforms::Sawtooth:
            sample = 2.0 * (m_phase / (2*kPi)) - 1.0;
            break;

        case Waveforms::Triangle:
            sample = 1.0 - 4.0 * std::abs(m_phase / (2*kPi) - 0.5);
            break;
    }

    m_phase += 2 * kPi * (m_frequency * std::pow(2, m_octave + m_detune / 1200.0)) / m_sampleRate;
    if (m_phase >= 2*kPi)
        m_phase -= 2*kPi;

    return (m_amplitude / 100.0) * sample;
}