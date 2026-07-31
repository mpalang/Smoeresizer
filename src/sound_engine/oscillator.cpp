#include <cmath>
#include "oscillator.h"

namespace {
    constexpr double kTwoPi = 6.283185307179586; // avoid M_PI (not standard on MSVC)
}

Oscillator::Oscillator(double sampleRate)
    : m_sampleRate(sampleRate)
{
}

void Oscillator::setFrequency(double freqHz)
{
    m_frequency = freqHz;
}

double Oscillator::nextSample()
{
    double sample = std::sin(m_phase);
    m_phase += kTwoPi * m_frequency / m_sampleRate;
    if (m_phase >= kTwoPi)
        m_phase -= kTwoPi;
    return sample;
}