 #include "keyboard.h"
 #include <QWidget>
 #include <QVBoxLayout>
 #include <QGridLayout>
 #include <QFrame>
 #include <QKeyEvent>
 #include "note.h"

 namespace{
    // binding order matches kNotes order
    // Windows scan codes — physical positions, QWERTZ labels for reference
    const quint32 kBindings[] = {
    0x1E, // A: C
    0x11, // W: C#
    0x1F, // S: D
    0x12, // E: D#
    0x20, // D: E
    0x21, // F: F
    0x14, // T: F#
    0x22, // G: G
    0x15, // Z: G#
    0x23, // H: A
    0x16, // U: A#
    0x24, // J: B
    0x25, //K: c
    0x18, //O: c#
    0x26, //L: d
    0x19, //P: d#
    0x27, //Ö: e
    0x28, //Ä: f
    0x1B, //+: f#
    0x2B //#: g
    };
};  

 Key::Key(const Note& note, QWidget* parent)
    : QPushButton(note.name, parent), m_note(note)
{   
    setFocusPolicy(Qt::NoFocus);
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
 
 Keyboard::Keyboard(QWidget* parent) : QWidget(parent)
{   
    setFocusPolicy(Qt::StrongFocus);

    auto* outer = new QVBoxLayout(this);
    //create keys
    auto* frame = new QFrame();
    frame->setFrameShape(QFrame::StyledPanel);

    QList<Key*> blackKeys;
    int position = 0;
    int i = 0;
    for (const auto& note : kNotes) {
        Key* key = nullptr;
        if (note.name.contains("#")){
            key = new BlackKey(note, frame);
            key->move(position - BlackKey::kWidth/2, 0);
            blackKeys.append(key);
        } else {
            key = new WhiteKey(note, frame);
            key->move(position, 0);
            position += WhiteKey::kWidth;
        }
        connect(key, &Key::notePressed, this, &Keyboard::notePressed);
        connect(key, &Key::noteReleased, this, &Keyboard::noteReleased);
        m_keyBindings.insert(kBindings[i], key);
        ++i;

    }
    for (Key* k : blackKeys)
        k->raise();
    frame->setFixedSize(position + WhiteKey::kWidth, WhiteKey::kHeight);
    outer->addWidget(frame);
    outer->addStretch();

}

void Keyboard::keyPressEvent(QKeyEvent* event)
{
    if (event->isAutoRepeat())
        return;

    if (Key* key = m_keyBindings.value(event->nativeScanCode(), nullptr)) {
        key->setDown(true);
        emit key->pressed();
        return;
    }
    QWidget::keyPressEvent(event);
}

void Keyboard::keyReleaseEvent(QKeyEvent* event)
{
    if (event->isAutoRepeat())
        return;

    if (Key* key = m_keyBindings.value(event->nativeScanCode(), nullptr)) {
        key->setDown(false);
        emit key->released();
        return;
    }
    QWidget::keyReleaseEvent(event);
}