#pragma once

#include <QWidget>
#include <QSpinBox>

class QSpinBox;

class EffectPanel : public QWidget
{
    Q_OBJECT

public:
    explicit EffectPanel(QWidget* parent = nullptr);

signals:
    void echoChanged(int percent);
    void distortionChanged(int percent);
    void delayChanged(int percent);
    void vibratoChanged(int percent);

private:
    QSpinBox* m_echo = nullptr;
    QSpinBox* m_distortion = nullptr;
    QSpinBox* m_delay = nullptr;
    QSpinBox* m_vibrato = nullptr;
};