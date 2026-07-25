#pragma once
#include <QIODevice>
#include "oscillator.h"

class AudioSource : public QIODevice
{
    Q_OBJECT

public:
    explicit AudioSource(QObject* parent = nullptr);

    void start();
    void stop();

    qint64 readData(char* data, qint64 maxlen) override;
    qint64 writeData(const char* data, qint64 len) override;
    bool isSequential() const override { return true; }
    qint64 bytesAvailable() const override; 

private:
    Oscillator m_oscillator;
};