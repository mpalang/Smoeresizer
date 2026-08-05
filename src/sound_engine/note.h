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
