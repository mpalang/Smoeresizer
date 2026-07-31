#pragma once
#include "widgets.h"

Key::Key(const Note& note, QWidget* parent)
    : QPushButton(note.name, parent), m_note(note)
{
    connect(this, &QPushButton::pressed, this, [this](){
        emit notePressed(m_note.frequency);
    });
    connect(this, &QPushButton::released, this, [this](){
        emit noteReleased(m_note.frequency);
    });
}

QString Key::noteName() const
{
    return m_note.name;
}

WhiteKey::WhiteKey(const Note& note, QWidget* parent)
    : Key(note, parent)
{    
    setFixedSize(kWidth, kHeight);
    setStyleSheet("QPushButton {background-color: white; color: black; border: 1px solid black;}"
                "QPushButton:pressed { background-color: #b0b0b0; }"
            );

}

BlackKey::BlackKey(const Note& note, QWidget* parent)
    : Key(note, parent)
{
    setFixedSize(kWidth, kHeight);
    setStyleSheet("QPushButton {background-color: black; color: white; border: 1px solid black;}"
                    "QPushButton:pressed { background-color: #b0b0b0; }"
                );
}