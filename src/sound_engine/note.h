#pragma once
#include <QString>
#include <vector>

struct Note
{
    QString name;
    double frequency;
};

// Standard 4th-octave frequencies (A4 = 440Hz reference)
inline const std::vector<Note> kNotes = {
    { "C", 261.63 },
    { "C#", 277.18 },
    { "D", 293.66 },
    { "D#", 311.13 },
    { "E", 329.63 },
    { "F", 349.23 },
    { "F#", 369.99 },
    { "G", 391.9954 },
    { "G#", 415.3047 },
    { "A", 440.00 },
    { "A#", 466.1638 },
    { "B", 493.8833 },
    { "c", 523.2511 },
    { "c#", 554.3653 },
    { "d", 587.3295 },
    { "d#", 622.2540 },
    { "e", 659.2551 },
    { "f", 698.4565 },
    { "f#", 739.9888 },
    { "g", 783.9909 },
};

// binding order matches kNotes order
// Windows scan codes — physical positions, QWERTZ labels for reference
static const quint32 kBindings[] = {
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