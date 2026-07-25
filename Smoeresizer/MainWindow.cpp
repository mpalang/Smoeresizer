#include "mainwindow.h"
#include <QMediaDevices>
#include <QDebug>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    setWindowTitle("My Synth");
    resize(400, 300);

    m_button = new QPushButton("Play", this);
    m_button->setGeometry(150, 130, 100, 40);
    connect(m_button, &QPushButton::clicked, this, &MainWindow::onButtonClicked);

    m_format.setSampleRate(44100);
    m_format.setChannelCount(1);
    m_format.setSampleFormat(QAudioFormat::Int16);

    m_device = QMediaDevices::defaultAudioOutput();
    if (!m_device.isFormatSupported(m_format))
        m_format = m_device.preferredFormat();

    m_audioSink = new QAudioSink(m_device, m_format, this);
    m_audioSource = new AudioSource(this);
}

void MainWindow::onButtonClicked()
{
    if (!m_playing) {
        m_audioSource->start();
        m_audioSink->start(m_audioSource);

        qDebug() << "Sink error:" << m_audioSink->error();
        qDebug() << "Sink state:" << m_audioSink->state();
        qDebug() << "Format:" << m_format;
        qDebug() << "Device:" << m_device.description();
        qDebug() << "Source isOpen:" << m_audioSource->isOpen();

        m_button->setText("Stop");
    }
    else {
        m_audioSink->stop();
        m_audioSource->stop();
        m_button->setText("Play");
    }
    m_playing = !m_playing;
}