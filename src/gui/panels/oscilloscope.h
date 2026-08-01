#pragma once
#include <QWidget>
#include <QMutex>
#include <vector>

class Oscilloscope : public QWidget
{
    Q_OBJECT

public:
    explicit Oscilloscope(QWidget* parent = nullptr);

    void pushSamples(const float* data, int count);  // called from audio thread

protected:
    void paintEvent(QPaintEvent* event) override;

private:
    QMutex m_mutex;
    std::vector<float> m_capture;   // bigger than what we draw
    int m_displayLength = 1024;
};