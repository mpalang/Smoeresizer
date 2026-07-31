#pragma once
#include "note.h"
#include "widgets.h"
#include <QPushButton>


class Key : public QPushButton
{
    Q_OBJECT

public: 
    explicit Key(const Note& note, QWidget* parent = nullptr);

    QString noteName() const;   

signals:
    void notePressed(double frequency);
    void noteReleased(double frequency);

private:
    Note m_note;
};

class WhiteKey : public Key
{
    Q_OBJECT

public:
    explicit WhiteKey(const Note& note, QWidget* parent = nullptr);
    static constexpr int kWidth = 40;
    static constexpr int kHeight = 200;
private:

};

class BlackKey : public Key
{
    Q_OBJECT

public:
    explicit BlackKey(const Note& note, QWidget* parent = nullptr);
    static constexpr int kWidth = 30;
    static constexpr int kHeight = 180;
private:

};
