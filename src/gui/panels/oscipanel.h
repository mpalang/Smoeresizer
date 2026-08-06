#pragma once

#include <QWidget>

#include "oscillatorsettings.h"

class QSpinBox;
class QComboBox;

class OscillatorPanel : public QWidget
{
    Q_OBJECT

public:
    explicit OscillatorPanel(const QString& name, QWidget* parent = nullptr);

signals:
    void settingsChanged(const OscillatorSettings& settings);

private:
    OscillatorSettings currentSettings() const;
    void emitSettings();
    QString m_name;
    QComboBox* m_waveform = nullptr;
    QSpinBox* m_amplitude = nullptr;
    QSpinBox* m_octave = nullptr;
    QSpinBox* m_detune = nullptr;


};