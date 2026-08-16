#pragma once

#include <QWidget>

class MySpinBox;
class QComboBox;

struct MasterSettings
{
    int Volume = 50;
    int EQLow = 0;
    int EQMid = 0;
    int EQHigh = 0;
};

class MasterPanel : public QWidget
{
    Q_OBJECT

public:
    explicit MasterPanel(QWidget* parent = nullptr);

signals:
    void settingsChanged(const MasterSettings& settings);

private:
    MasterSettings currentSettings() const;
    void emitSettings();
    MySpinBox* m_Volume = nullptr;
    MySpinBox* m_EQLow = nullptr;
    MySpinBox* m_EQMid = nullptr;
    MySpinBox* m_EQHigh = nullptr;

};

