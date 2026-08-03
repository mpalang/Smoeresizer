#include "oscipanel.h"

#include <QGridLayout>
#include <QLabel>
#include <QSpinBox>
#include <QComboBox>

#include "oscillator.h"

OscillatorPanel::OscillatorPanel(QWidget* parent)
    : QWidget(parent)
{
    // Create Widgets
    m_waveform = new QComboBox(this);
    m_waveform->addItem("Sine",     static_cast<int>(Oscillator::Waveforms::Sine));
    m_waveform->addItem("Square",   static_cast<int>(Oscillator::Waveforms::Square));
    m_waveform->addItem("Sawtooth",      static_cast<int>(Oscillator::Waveforms::Sawtooth));
    m_waveform->addItem("Triangle", static_cast<int>(Oscillator::Waveforms::Triangle));

    m_attack = new QSpinBox(this);
    m_attack->setRange(0, 100);
    m_attack->setValue(30);
    m_attack->setSuffix("%");

    m_decay = new QSpinBox(this);
    m_decay->setRange(0, 100);
    m_decay->setValue(30);
    m_decay->setSuffix("%");
    
    m_release = new QSpinBox(this);
    m_release->setRange(1, 100);
    m_release->setValue(5);
    m_release->setSuffix("%");

    // Create Layout
    
    auto* outer = new QVBoxLayout(this);

    auto* frame = new QFrame();
    frame->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    frame->setFrameShape(QFrame::StyledPanel);
    outer->addWidget(frame);

    auto* layout = new QGridLayout(frame);
    layout->addWidget(new QLabel("<b>Osci1</b>"), 0, 0);   
    layout->addWidget(new QLabel("Waveform", this),  1, 0);
    layout->addWidget(m_waveform,                    2, 0);
    layout->addWidget(new QLabel("Attack", this),  1, 1);
    layout->addWidget(m_attack,                     2, 1);
    layout->addWidget(new QLabel("Decay", this),   3, 0);
    layout->addWidget(m_decay,                      4, 0);
    layout->addWidget(new QLabel("Release", this),  3, 1);
    layout->addWidget(m_release,                    4, 1);



    // Connect Signals
    connect(m_waveform, &QComboBox::currentIndexChanged, this, [this](int i) {
        emit waveformChanged(static_cast<Oscillator::Waveforms>(m_waveform->itemData(i).toInt()));
    });
    connect(m_attack, &QSpinBox::valueChanged, this, &OscillatorPanel::attackChanged);
    connect(m_decay,  &QSpinBox::valueChanged, this, &OscillatorPanel::decayChanged);
    connect(m_release,  &QSpinBox::valueChanged, this, &OscillatorPanel::releaseChanged);
}