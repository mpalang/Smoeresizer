#pragma once

#include <QWidget>
#include <QPushButton>

class MySpinBox;

class EffectWidget : public QWidget
{
    Q_OBJECT

public:
    explicit EffectWidget(QWidget* parent = nullptr);


signals:
    void intensityChanged(int percent);

private:
    QPushButton* m_osc1Button = nullptr;
    QPushButton* m_osc2Button = nullptr;   
    MySpinBox* m_intensity = nullptr;
};


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