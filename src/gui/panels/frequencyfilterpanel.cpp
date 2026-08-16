#include "frequencyfilterpanel.h"

#include <QGridLayout>
#include <QLabel>
#include <QComboBox>

#include "widgets.h"

FrequencyFilterPanel::FrequencyFilterPanel(QWidget* parent)
    : QWidget(parent)
{   
    int WIDGETWIDTH = 100;
    // Create Widgets

    m_HPfilter = new MySpinBox(this);
    m_HPfilter->setRange(0, 100);
    m_HPfilter->setValue(50);
    m_HPfilter->setSuffix("%");
    m_HPfilter->setFixedWidth(WIDGETWIDTH);

    m_LPfilter = new MySpinBox(this);
    m_LPfilter->setRange(0, 100);
    m_LPfilter->setValue(50);
    m_LPfilter->setSuffix("%");
    m_LPfilter->setFixedWidth(WIDGETWIDTH);

    // Create Layout
    auto* outer = new QVBoxLayout(this);

    auto* frame = new QFrame();
    frame->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    frame->setFrameShape(QFrame::StyledPanel);
    outer->addWidget(frame);

    auto* layout = new QGridLayout(frame);
    layout->addWidget(new QLabel("<b> Frequency Filter </b>"), 0, 0); 
    layout->addWidget(new QLabel("Low Pass"), 1, 0);
    layout->addWidget(m_LPfilter,              2, 0);
    layout->addWidget(new QLabel("High Pass", this),  1, 1);
    layout->addWidget(m_HPfilter,                     2, 1);


    // Connect Signals
    connect(m_LPfilter, &MySpinBox::valueChanged, this, &FrequencyFilterPanel::emitSettings);
    connect(m_HPfilter, &MySpinBox::valueChanged, this, &FrequencyFilterPanel::emitSettings);

}

FrequencyFilterSettings FrequencyFilterPanel::currentSettings() const
{
    FrequencyFilterSettings s;
    return s;
}

void FrequencyFilterPanel::emitSettings()
{
    emit settingsChanged(currentSettings());
}