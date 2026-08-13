#pragma once

#include <QWidget>

class QSpinBox;
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
    QSpinBox* m_HPfilter = nullptr;
    QSpinBox* m_LPfilter = nullptr;

};

