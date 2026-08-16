#include "oscipanel.h"

#include <QGridLayout>
#include <QLabel>
#include <QComboBox>

#include "widgets.h"
#include "styling.h"

OscillatorPanel::OscillatorPanel(const QString& name, QWidget* parent)
    : QWidget(parent), m_name(name)
{   
    // int WIDGETWIDTH = 100;
    // Create Widgets
    m_waveform = new QComboBox(this);
    m_waveform->addItem(Styling::makeWaveIcon(Oscillator::Waveforms::Sine), "",     static_cast<int>(Oscillator::Waveforms::Sine));
    m_waveform->addItem(Styling::makeWaveIcon(Oscillator::Waveforms::Square), "",   static_cast<int>(Oscillator::Waveforms::Square));
    m_waveform->addItem(Styling::makeWaveIcon(Oscillator::Waveforms::Sawtooth), "",      static_cast<int>(Oscillator::Waveforms::Sawtooth));
    m_waveform->addItem(Styling::makeWaveIcon(Oscillator::Waveforms::Triangle), "", static_cast<int>(Oscillator::Waveforms::Triangle));
    // m_waveform->setFixedWidth(WIDGETWIDTH);

    m_amplitude = new MySpinBox(this);
    m_amplitude->setRange(0, 100);
    m_amplitude->setValue(50);
    m_amplitude->setSuffix("%");
    // m_amplitude->setFixedWidth(WIDGETWIDTH);

    m_octave = new MySpinBox(this);
    m_octave->setRange(-5, 5);
    m_octave->setValue(0);
    // m_octave->setFixedWidth(WIDGETWIDTH);

    m_detune = new MySpinBox(this);
    m_detune->setRange(-100, 100);
    m_detune->setValue(0);
    m_detune->setSuffix(" cts");
    // m_detune->setFixedWidth(WIDGETWIDTH);

    // Create Layout
    auto* outer = new QVBoxLayout(this);

    auto* frame = new QFrame();
    frame->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    frame->setFrameShape(QFrame::StyledPanel);
    outer->addWidget(frame);

    auto* layout = new QGridLayout(frame);
    layout->addWidget(new QLabel("<b>" + m_name + "</b>"), 0, 0); 
    layout->addWidget(new QLabel("Amplitude"), 1, 0);
    layout->addWidget(m_amplitude,              2, 0);
    layout->addWidget(new QLabel("Octave", this),  1, 1);
    layout->addWidget(m_octave,                     2, 1);
    layout->addWidget(new QLabel("Waveform", this),  3, 0);
    layout->addWidget(m_waveform,                    4, 0);
    layout->addWidget(new QLabel("Detune", this), 3, 1);
    layout->addWidget(m_detune,                   4, 1);

    // Connect Signals
    connect(m_waveform, &QComboBox::currentIndexChanged, this, &OscillatorPanel::emitSettings);
    connect(m_amplitude, &MySpinBox::valueChanged, this, &OscillatorPanel::emitSettings);
    connect(m_octave, &MySpinBox::valueChanged, this, &OscillatorPanel::emitSettings);
    connect(m_detune, &MySpinBox::valueChanged, this, &OscillatorPanel::emitSettings);
}

OscillatorSettings OscillatorPanel::currentSettings() const
{
    OscillatorSettings s;
    s.waveform = static_cast<Oscillator::Waveforms>(
        m_waveform->currentData().toInt());
    s.octave = m_octave->value();
    s.amplitude = m_amplitude->value();
    s.detune = m_detune->value(); //detune in cents.
    return s;
}

void OscillatorPanel::emitSettings()
{
    emit settingsChanged(currentSettings());
}