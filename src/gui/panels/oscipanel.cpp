#include "oscipanel.h"

#include <QGridLayout>
#include <QLabel>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QComboBox>

#include "oscillator.h"

OscillatorPanel::OscillatorPanel(const QString& name, QWidget* parent)
    : QWidget(parent), m_name(name)
{   
    int WIDGETWIDTH = 80;
    // Create Widgets
    m_waveform = new QComboBox(this);
    m_waveform->addItem("Sin",     static_cast<int>(Oscillator::Waveforms::Sine));
    m_waveform->addItem("Squ",   static_cast<int>(Oscillator::Waveforms::Square));
    m_waveform->addItem("Saw",      static_cast<int>(Oscillator::Waveforms::Sawtooth));
    m_waveform->addItem("Tri", static_cast<int>(Oscillator::Waveforms::Triangle));
    m_waveform->setFixedWidth(WIDGETWIDTH);

    m_amplitude = new QSpinBox(this);
    m_amplitude->setRange(0, 100);
    m_amplitude->setValue(50);
    m_amplitude->setSuffix("%");
    m_amplitude->setFixedWidth(WIDGETWIDTH);

    m_octave = new QSpinBox(this);
    m_octave->setRange(-5, 5);
    m_octave->setValue(0);
    m_octave->setFixedWidth(WIDGETWIDTH);

    m_detune = new QSpinBox(this);
    m_detune->setRange(-100, 100);
    m_detune->setValue(0);
    m_detune->setSuffix(" cts");
    m_detune->setFixedWidth(WIDGETWIDTH);

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
    connect(m_waveform, &QComboBox::currentIndexChanged, this, [this](int i) {
        emit waveformChanged(static_cast<Oscillator::Waveforms>(m_waveform->itemData(i).toInt()));
    });
    connect(m_amplitude, &QSpinBox::valueChanged, this, &OscillatorPanel::amplitudeChanged);
    connect(m_octave, &QSpinBox::valueChanged, this, &OscillatorPanel::octaveChanged);
    connect(m_detune, &QSpinBox::valueChanged, this, &OscillatorPanel::detuneChanged);
}