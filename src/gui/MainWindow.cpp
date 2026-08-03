#include "mainwindow.h"
#include "note.h"
#include "widgets.h"
#include "effectpanel.h"
#include "oscipanel.h"
#include "oscilloscope.h"
#include <QWidget>
#include <QFrame>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QKeyEvent>
#include <QMediaDevices>


MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    setWindowTitle("Smoeresizer");
    resize(400, 300);

    setupAudio();
    create_ui();

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

void MainWindow::create_ui()
{
    // Create Layout:
    auto* central = new QWidget(this);
    setCentralWidget(central);

    auto* outerLayout = new QHBoxLayout(central);

    auto* leftLayout = new QVBoxLayout();
    outerLayout->addLayout(leftLayout);
    auto* middleLayout = new QVBoxLayout();
    outerLayout->addLayout(middleLayout);
    auto* rightLayout = new QVBoxLayout();
    outerLayout->addLayout(rightLayout);

    // Left Panel
    auto* oscillatorPanel1 = new OscillatorPanel();
    leftLayout->addWidget(oscillatorPanel1);
    connect(oscillatorPanel1, &OscillatorPanel::waveformChanged,
        this, [this](Oscillator::Waveforms w) { m_audioSource->setWaveform(w); });

    auto* oscillatorPanel2 = new OscillatorPanel();
    leftLayout->addWidget(oscillatorPanel2);
    connect(oscillatorPanel2, &OscillatorPanel::waveformChanged,
        this, [this](Oscillator::Waveforms w) { m_audioSource->setWaveform(w); });

    // Middle Panel
    auto* oscilloscope = new Oscilloscope();
    m_audioSource->setOscilloscope(oscilloscope);
    middleLayout->addWidget(oscilloscope);

    //create keys
    auto* keyboardFrame = new QFrame();
    keyboardFrame->setFrameShape(QFrame::StyledPanel);

    QList<Key*> blackKeys;
    float position = - WhiteKey::kWidth;
    int i = 0;
    for (const auto& note : kNotes) {
        Key* key = nullptr;
        if (note.name.contains("#")){
            key = new BlackKey(note, keyboardFrame);
            key->move(position + WhiteKey::kWidth - BlackKey::kWidth/2, 0);
            blackKeys.append(key);
            connect(key, &Key::notePressed, this, [this](double f) { m_audioSource->noteOn(f); });
            connect(key, &Key::noteReleased, this, [this](double f) { m_audioSource->noteOff(f); });
        } else {
            position = position + WhiteKey::kWidth;
            key = new WhiteKey(note, keyboardFrame);
            key->move(position, 0);
            connect(key, &Key::notePressed, this, [this](double f) { m_audioSource->noteOn(f); });
            connect(key, &Key::noteReleased, this, [this](double f) { m_audioSource->noteOff(f); });
        }
        m_keyBindings.insert(kBindings[i], key);
        ++i;

    }
    for (Key* k : blackKeys)
        k->raise();
    keyboardFrame->setFixedSize(static_cast<int>(position) + 40, 200);
    middleLayout->addWidget(keyboardFrame);
    middleLayout->addStretch();

    // Right Panel
    auto* effectPanel2 = new EffectPanel();
    rightLayout->addWidget(effectPanel2);
}

void MainWindow::keyPressEvent(QKeyEvent* event)
{
    if (event->isAutoRepeat())
        return;

    if (Key* key = m_keyBindings.value(event->nativeScanCode(), nullptr)) {
        key->setDown(true);
        emit key->pressed();
        return;
    }
    QMainWindow::keyPressEvent(event);
}

void MainWindow::keyReleaseEvent(QKeyEvent* event)
{
    if (event->isAutoRepeat())
        return;

    if (Key* key = m_keyBindings.value(event->nativeScanCode(), nullptr)) {
        key->setDown(false);
        emit key->released();
        return;
    }
    QMainWindow::keyReleaseEvent(event);
}