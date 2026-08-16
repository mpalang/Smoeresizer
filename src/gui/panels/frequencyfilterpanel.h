#pragma once

#include <QWidget>

class MySpinBox;
class QComboBox;

struct FrequencyFilterSettings
{
    int highpass = 0;
    float lowpass = 1.0f;
};

class FrequencyFilterPanel : public QWidget
{
    Q_OBJECT

public:
    explicit FrequencyFilterPanel(QWidget* parent = nullptr);

signals:
    void settingsChanged(const FrequencyFilterSettings& settings);

private:
    FrequencyFilterSettings currentSettings() const;
    void emitSettings();
    MySpinBox* m_HPfilter = nullptr;
    MySpinBox* m_LPfilter = nullptr;

};

