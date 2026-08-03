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
    void attackChanged(int percent);
    void decayChanged(int percent);
    void releaseChanged(int percent);

private:
    QComboBox* m_waveform = nullptr;
    QSpinBox* m_attack = nullptr;
    QSpinBox* m_decay = nullptr;
    QSpinBox* m_release = nullptr;
};