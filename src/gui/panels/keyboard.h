#pragma once

#include <QWidget>
#include <QHash>
#include <QPushButton>

#include "note.h"

class QKeyEvent;

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

};

class BlackKey : public Key
{
    Q_OBJECT

public:
    explicit BlackKey(const Note& note, QWidget* parent = nullptr);
    static constexpr int kWidth = 30;
    static constexpr int kHeight = 120;

};


class Keyboard : public QWidget
{
    Q_OBJECT

public:
    explicit Keyboard(QWidget* parent = nullptr);

signals:
    void notePressed(double frequency);
    void noteReleased(double frequency);

protected:
    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent* event) override;

private:
    QHash<quint32, Key*> m_keyBindings;
};