#include "mainwindow.h"
#include "note.h"
#include "widgets.h"
#include <QWidget>
#include <QFrame>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QKeyEvent>
#include <QMediaDevices>


MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    setWindowTitle("My Synth");
    resize(400, 300);

    setupAudio();
    setupKeyboard();

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

void MainWindow::setupKeyboard()
{
        auto* central = new QWidget(this);
    setCentralWidget(central);
    auto* outerLayout = new QVBoxLayout(central);

    //create keys
    auto* keyboardFrame = new QFrame(central);
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

        // keyLayout->addWidget(key);
        m_keyBindings.insert(kBindings[i], key);
        ++i;
    }
    for (Key* k : blackKeys)
        k->raise();

    keyboardFrame->setFixedSize(static_cast<int>(position) + 40, 200);
    outerLayout->addWidget(keyboardFrame);
    outerLayout->addStretch();
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