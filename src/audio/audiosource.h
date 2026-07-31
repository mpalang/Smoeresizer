#pragma once
#include <QIODevice>
#include <vector>
#include "synthengine.h"

class AudioSource : public QIODevice
{
    Q_OBJECT

public:
    explicit AudioSource(QObject* parent = nullptr);

    void start();
    void stop();

    void noteOn(double frequency);
    void noteOff(double frequency);

    qint64 readData(char* data, qint64 maxlen) override;
    qint64 writeData(const char* data, qint64 len) override;
    bool isSequential() const override { return true; }
    qint64 bytesAvailable() const override; 

private:
    SynthEngine m_engine;
    std::vector<float> m_buffer;
};