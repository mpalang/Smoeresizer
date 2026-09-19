#pragma once

#include <vector>

class MasterProcessor
{
public:
    void setGain(float volume) { m_volume = volume; }   // 0.0 - 1.0 (or higher)

    void process(std::vector<float>& buffer);

private:
    float m_volume = 0.3f;
    float m_smoothed = 0.3f;
};