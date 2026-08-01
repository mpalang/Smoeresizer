#include "effectpanel.h"

#include <QGridLayout>
#include <QLabel>
#include <QSpinBox>

EffectPanel::EffectPanel(QWidget* parent)
    : QWidget(parent)
{
    auto* layout = new QGridLayout(this);

    m_echo = new QSpinBox(this);
    m_echo->setRange(1, 100);
    m_echo->setValue(5);
    m_echo->setSuffix("%");

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

    layout->addWidget(new QLabel("Echo", this),  0, 0);
    layout->addWidget(m_echo,                    0, 1);
    layout->addWidget(new QLabel("Distortion", this), 1, 0);
    layout->addWidget(m_distortion,                   1, 1);
    layout->addWidget(new QLabel("Delay", this),  2, 0);
    layout->addWidget(m_delay,                    2, 1);
    layout->addWidget(new QLabel("Vibrato", this),  3, 0);
    layout->addWidget(m_vibrato,                    3, 1);

    connect(m_echo,  &QSpinBox::valueChanged, this, &EffectPanel::echoChanged);
    connect(m_distortion, &QSpinBox::valueChanged, this, &EffectPanel::distortionChanged);
    connect(m_delay,  &QSpinBox::valueChanged, this, &EffectPanel::delayChanged);
    connect(m_vibrato,  &QSpinBox::valueChanged, this, &EffectPanel::vibratoChanged);
}