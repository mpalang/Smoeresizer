#include "masterpanel.h"

#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <QComboBox>

#include "widgets.h"

MasterPanel::MasterPanel(QWidget* parent)
    : QWidget(parent)
{   
    // int WIDGETWIDTH = 100;
    // Create Widgets

    m_Volume = new MySpinBox(this);
    m_Volume->setRange(-100, 100);
    m_Volume->setValue(0);
    m_Volume->setSuffix("%");
    // m_Volume->setFixedWidth(WIDGETWIDTH);

    m_EQLow = new MySpinBox(this);
    m_EQLow->setRange(-100, 100);
    m_EQLow->setValue(0);
    m_EQLow->setSuffix("%");
    // m_EQLow->setFixedWidth(WIDGETWIDTH);

    m_EQMid = new MySpinBox(this);
    m_EQMid->setRange(-100, 100);
    m_EQMid->setValue(0);
    m_EQMid->setSuffix("%");
    // m_EQMid->setFixedWidth(WIDGETWIDTH);

    m_EQHigh = new MySpinBox(this);
    m_EQHigh->setRange(-100, 100);
    m_EQHigh->setValue(0);
    m_EQHigh->setSuffix("%");
    // m_EQHigh->setFixedWidth(WIDGETWIDTH);

    // Create Layout
    auto* outer = new QVBoxLayout(this);

    auto* frame = new QFrame();
    frame->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    frame->setFrameShape(QFrame::StyledPanel);
    outer->addWidget(frame);

    auto* layout = new QGridLayout(frame);
    layout->addWidget(new QLabel("<b> Master </b>"), 0, 0); 
    layout->addWidget(new QLabel("Volume"),    1, 0);
    layout->addWidget(m_Volume,                2, 0);
    layout->addWidget(new QLabel("Low", this), 1, 1);
    layout->addWidget(m_EQLow,                 2, 1);
    layout->addWidget(new QLabel("Mid", this), 1, 2);
    layout->addWidget(m_EQMid,                 2, 2);
    layout->addWidget(new QLabel("High", this),1, 3);
    layout->addWidget(m_EQHigh,                2, 3);

    // Connect Signals
    connect(m_Volume, &MySpinBox::valueChanged, this, &MasterPanel::emitSettings);
    connect(m_EQLow, &MySpinBox::valueChanged, this, &MasterPanel::emitSettings);
    connect(m_EQMid, &MySpinBox::valueChanged, this, &MasterPanel::emitSettings);
    connect(m_EQHigh, &MySpinBox::valueChanged, this, &MasterPanel::emitSettings);

}

MasterSettings MasterPanel::currentSettings() const
{
    MasterSettings s;
    return s;
}

void MasterPanel::emitSettings()
{
    emit settingsChanged(currentSettings());
}