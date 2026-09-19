#include "masterprocessor.h"

#include <algorithm>
#include <cmath>

void MasterProcessor::process(std::vector<float>& buffer)
{
    constexpr float kSmoothing = 0.0005f;

    for (auto& s : buffer) {
        m_smoothed += (m_volume - m_smoothed) * kSmoothing;
        s = std::tanh(s * m_smoothed);
    }
}