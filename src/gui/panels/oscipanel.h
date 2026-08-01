#pragma once

#include <QWidget>
#include <QSpinBox>

#include "oscillator.h"

class QSpinBox;
class QComboBox;

class OscillatorPanel : public QWidget
{
    Q_OBJECT

public:
    explicit OscillatorPanel(QWidget* parent = nullptr);

signals:
    void waveformChanged(Oscillator::Waveforms waveform);
    void distortionChanged(int percent);
    void delayChanged(int percent);
    void vibratoChanged(int percent);

private:
    QComboBox* m_waveform = nullptr;
    QSpinBox* m_distortion = nullptr;
    QSpinBox* m_delay = nullptr;
    QSpinBox* m_vibrato = nullptr;
};