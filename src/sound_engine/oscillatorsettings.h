#pragma once

#include "oscillator.h"

struct OscillatorSettings
{
    Oscillator::Waveforms waveform = Oscillator::Waveforms::Sine;
    int octave = 0;
    float amplitude = 1.0f;
    int detune = 0;
};