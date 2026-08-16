#pragma once

#include <QWidget>

class MySpinBox;

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
    MySpinBox* m_echo = nullptr;
    MySpinBox* m_distortion = nullptr;
    MySpinBox* m_delay = nullptr;
    MySpinBox* m_vibrato = nullptr;
};