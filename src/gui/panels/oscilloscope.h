#pragma once
#include <QWidget>
#include <QMutex>
#include <vector>

class Oscilloscope : public QWidget
{
    Q_OBJECT

public:
    explicit Oscilloscope(QWidget* parent = nullptr);

    enum class Mode {Waveform, Spectrum};

    void pushSamples(const float* data, int count);  // called from audio thread

public slots:
    void setMode(Mode mode);

protected:
    void paintEvent(QPaintEvent* event) override;

private:
    void paintWaveform(QPainter& p, const std::vector<float>& samples);
    void paintSpectrum(QPainter& p, const std::vector<float>& samples);

    QMutex m_mutex;
    std::vector<float> m_capture;
    int m_displayLength = 1024;
    Mode m_mode = Mode::Waveform;
    float m_scale = 1.0f;
};