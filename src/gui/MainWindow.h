#pragma once
#include <QMainWindow>
#include <QHash>
#include <QAudioSink>
#include <QAudioFormat>
#include <QAudioDevice>
#include "audiosource.h"
#include "widgets.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);

protected:
    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent* event) override;

private:
    QHash<quint32, Key*> m_keyBindings;
    QAudioSink* m_audioSink = nullptr;
    AudioSource* m_audioSource = nullptr;

    void setupAudio();
    void setupKeyboard();

};