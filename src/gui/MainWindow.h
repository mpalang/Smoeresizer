#pragma once
#include <QMainWindow>
#include <QAudioSink>
#include <QAudioFormat>
#include <QAudioDevice>

class AudioSource;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);

private:
    QAudioSink* m_audioSink = nullptr;
    AudioSource* m_audioSource = nullptr;
    
    void setupStatusBar();
    void updateStatus();
    void setupAudio();
    void createUi();

    QLabel* m_latencyLabel = nullptr;
    QLabel* m_deviceLabel = nullptr;

};