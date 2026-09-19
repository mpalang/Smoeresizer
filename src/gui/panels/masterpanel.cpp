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
    m_Volume->setRange(0, 100);
    m_Volume->setValue(50);
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
    layout->addWidget(new QLabel("<b> EQ </b>"), 0, 2); 
    QFrame* hline = new QFrame(frame);
    hline->setFrameShape(QFrame::HLine);
    hline->setFrameShadow(QFrame::Sunken);
    layout->addWidget(hline, 1, 1, 1, 3);
    layout->addWidget(new QLabel("Volume"),    2, 0);
    layout->addWidget(m_Volume,                3, 0);
    layout->addWidget(new QLabel("Low", this), 2, 1);
    layout->addWidget(m_EQLow,                 3, 1);
    layout->addWidget(new QLabel("Mid", this), 2, 2);
    layout->addWidget(m_EQMid,                 3, 2);
    layout->addWidget(new QLabel("High", this),2, 3);
    layout->addWidget(m_EQHigh,                3, 3);

    // Connect Signals
    connect(m_Volume, &MySpinBox::valueChanged, this, &MasterPanel::emitSettings);
    connect(m_EQLow, &MySpinBox::valueChanged, this, &MasterPanel::emitSettings);
    connect(m_EQMid, &MySpinBox::valueChanged, this, &MasterPanel::emitSettings);
    connect(m_EQHigh, &MySpinBox::valueChanged, this, &MasterPanel::emitSettings);

}

MasterSettings MasterPanel::currentSettings() const
{
    MasterSettings s;

    s.Volume = m_Volume->value();
    s.EQHigh = m_EQHigh->value();
    s.EQMid = m_EQMid->value();
    s.EQLow = m_EQLow->value();

    return s;
}

void MasterPanel::emitSettings()
{
    emit settingsChanged(currentSettings());
}