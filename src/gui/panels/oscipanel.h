#pragma once

#include <QWidget>

#include "oscillatorsettings.h"

class MySpinBox;
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
    MySpinBox* m_amplitude = nullptr;
    MySpinBox* m_octave = nullptr;
    MySpinBox* m_detune = nullptr;

};