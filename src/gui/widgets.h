#pragma once

#include <QSpinBox>

class MySpinBox : public QSpinBox
{
    Q_OBJECT

public:
    explicit MySpinBox(QWidget* parent = nullptr);
};