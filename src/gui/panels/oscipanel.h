#pragma once

#include <QWidget>

#include "oscillator.h"

class QSpinBox;
class QComboBox;
class QDoubleSpinBox;

class OscillatorPanel : public QWidget
{
    Q_OBJECT

public:
    explicit OscillatorPanel(const QString& name, QWidget* parent = nullptr);

signals:
    void waveformChanged(Oscillator::Waveforms waveform);
    void amplitudeChanged(int percent);
    void octaveChanged(int octave);
    void detuneChanged(int cents);

private:
    QString m_name;
    QSpinBox* m_amplitude = nullptr;
    QSpinBox* m_octave = nullptr;
    QSpinBox* m_detune = nullptr;
    QComboBox* m_waveform = nullptr;

};