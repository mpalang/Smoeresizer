#include "mainwindow.h"

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMediaDevices>
#include <QStatusBar>
#include <QLabel>
#include <QTimer>

#include "effectpanel.h"
#include "oscipanel.h"
#include "oscilloscope.h"
#include "keyboard.h"
#include "audiosource.h"
#include "frequencyfilterpanel.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    setWindowTitle("Smoeresizer");
    resize(450, 350);

    setupAudio();
    createUi();
    setupStatusBar();

}

void MainWindow::setupAudio()
{
    QAudioFormat format;
    format.setSampleRate(44100);
    format.setChannelCount(1);
    format.setSampleFormat(QAudioFormat::Int16);

    QAudioDevice device = QMediaDevices::defaultAudioOutput();
    if (!device.isFormatSupported(format))
        format = device.preferredFormat();

    m_audioSource = new AudioSource(this);
    m_audioSource->start();

    m_audioSink = new QAudioSink(device, format, this);
    m_audioSink->setBufferSize(1024);
    m_audioSink->start(m_audioSource);
}

void MainWindow::createUi()
{
    // Create Layout:
    auto* central = new QWidget(this);
    setCentralWidget(central);

    auto* outerLayout = new QHBoxLayout(central);

    // Create three vertical layouts for left, middle, and right panels
    auto* leftLayout = new QVBoxLayout();
    outerLayout->addLayout(leftLayout);
    auto* middleLayout = new QVBoxLayout();
    outerLayout->addLayout(middleLayout);
    auto* rightLayout = new QVBoxLayout();
    outerLayout->addLayout(rightLayout);

    // Left Panel
    auto* osciPanel1 = new OscillatorPanel("Osci1");
    leftLayout->addWidget(osciPanel1);
    connect(osciPanel1, &OscillatorPanel::settingsChanged,
        this, [this](const OscillatorSettings& s) { m_audioSource->setOscillator(0, s); });

    auto* osciPanel2 = new OscillatorPanel("Osci2");
    leftLayout->addWidget(osciPanel2);
    connect(osciPanel2, &OscillatorPanel::settingsChanged,
        this, [this](const OscillatorSettings& s) { m_audioSource->setOscillator(1, s); });

    auto* filterPanel = new FrequencyFilterPanel();
    leftLayout->addWidget(filterPanel);


    // Middle Panel
    auto* oscilloscope = new Oscilloscope();
    m_audioSource->setOscilloscope(oscilloscope);
    middleLayout->addWidget(oscilloscope);
    
    auto* keyboard = new Keyboard();
    middleLayout->addWidget(keyboard);
    keyboard->setFocus();

    connect(keyboard, &Keyboard::notePressed, this, [this](double f) { m_audioSource->noteOn(f); });
    connect(keyboard, &Keyboard::noteReleased, this, [this](double f) { m_audioSource->noteOff(f); });

    // Right Panel
    auto* effectPanel2 = new EffectPanel();
    rightLayout->addWidget(effectPanel2);
}

void MainWindow::setupStatusBar()
{
    m_deviceLabel = new QLabel();
    m_latencyLabel = new QLabel();

    statusBar()->addWidget(m_deviceLabel);
    statusBar()->addPermanentWidget(m_latencyLabel);

    m_deviceLabel->setText(QMediaDevices::defaultAudioOutput().description());

    updateStatus();

    auto* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateStatus);
    timer->start(500);
}

void MainWindow::updateStatus()
{
    const int bytes = m_audioSink->bufferSize();
    const double ms = bytes / 2.0 / 44100.0 * 1000.0;

    m_latencyLabel->setText(
        QString("Voices: %1").arg(m_audioSource->activeVoices()));
}