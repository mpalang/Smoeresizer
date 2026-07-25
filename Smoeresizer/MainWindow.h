#pragma once
#include <QMainWindow>
#include <QPushButton>
#include <QAudioSink>
#include <QAudioFormat>
#include <QAudioDevice>
#include "audiosource.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);

private slots:
    void onButtonClicked();

private:
    QPushButton* m_button;
    QAudioSink* m_audioSink = nullptr;
    AudioSource* m_audioSource = nullptr;
    bool m_playing = false;

    QAudioFormat m_format;   // <-- added
    QAudioDevice m_device;   // <-- added
};