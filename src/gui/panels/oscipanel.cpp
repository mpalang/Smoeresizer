#include "oscipanel.h"

#include <QGridLayout>
#include <QLabel>
#include <QSpinBox>
#include <QComboBox>

#include "oscillator.h"

OscillatorPanel::OscillatorPanel(QWidget* parent)
    : QWidget(parent)
{
    auto* layout = new QGridLayout(this);

    m_waveform = new QComboBox(this);
    m_waveform->addItem("Sine",     static_cast<int>(Oscillator::Waveforms::Sine));
    m_waveform->addItem("Square",   static_cast<int>(Oscillator::Waveforms::Square));
    m_waveform->addItem("Sawtooth",      static_cast<int>(Oscillator::Waveforms::Sawtooth));
    m_waveform->addItem("Triangle", static_cast<int>(Oscillator::Waveforms::Triangle));


    m_distortion = new QSpinBox(this);
    m_distortion->setRange(0, 100);
    m_distortion->setValue(30);
    m_distortion->setSuffix("%");
    
    m_delay = new QSpinBox(this);
    m_delay->setRange(1, 100);
    m_delay->setValue(5);
    m_delay->setSuffix("%");

    m_vibrato = new QSpinBox(this);
    m_vibrato->setRange(0, 100);
    m_vibrato->setValue(30);
    m_vibrato->setSuffix("%");

    layout->addWidget(new QLabel("Waveform", this),  0, 0);
    layout->addWidget(m_waveform,                    0, 1);
    layout->addWidget(new QLabel("Distortion", this), 1, 0);
    layout->addWidget(m_distortion,                   1, 1);
    layout->addWidget(new QLabel("Delay", this),  2, 0);
    layout->addWidget(m_delay,                    2, 1);
    layout->addWidget(new QLabel("Vibrato", this),  3, 0);
    layout->addWidget(m_vibrato,                    3, 1);

    connect(m_waveform, &QComboBox::currentIndexChanged, this, [this](int i) {
        emit waveformChanged(static_cast<Oscillator::Waveforms>(m_waveform->itemData(i).toInt()));
    });
    connect(m_distortion, &QSpinBox::valueChanged, this, &OscillatorPanel::distortionChanged);
    connect(m_delay,  &QSpinBox::valueChanged, this, &OscillatorPanel::delayChanged);
    connect(m_vibrato,  &QSpinBox::valueChanged, this, &OscillatorPanel::vibratoChanged);
}