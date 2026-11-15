Smoeresizer

A synthesizer app built from scratch to play around with sounds and effects, and to get a better understanding of how synthesis works under the hood.

v0 — a waveform of a given frequency is generated, modified by effects, and played through the system's default audio output.

Features
Polyphonic engine — multiple notes can be held at once, each with its own voice and envelope
Two oscillators per voice — selectable waveform (sine, square, saw, triangle), octave offset and amplitude
On-screen keyboard — mouse-clickable keys plus computer-keyboard bindings (mapped by physical scan code, so the layout stays consistent)
Oscilloscope — triggered time-domain view and an FFT frequency-domain view
Master section — output gain with soft clipping, peak metering in the status bar
Architecture

The audio engine is pure C++ with no Qt dependency; Qt is only used for the GUI and for audio output.

AudioSource    Qt glue — QIODevice, float to int16 conversion
SynthEngine    voice pool, note routing, shared oscillator settings
Voice          one held note — oscillators plus amplitude envelope
Oscillator     one waveform generator

Each layer only knows about the one below it. GUI widgets emit signals describing what happened; MainWindow routes them to the audio side, so no widget talks to the engine directly.

src/
├── main.cpp
├── gui/          windows, panels, keyboard, oscilloscope
├── sound_engine/ oscillator, voice, synth engine, master chain
├── audio/        audio output / Qt audio device handling
└── utils/        FFT and other generic helpers
Requirements
Qt 6.11.1 (MSVC 2022, 64-bit)
Visual Studio Build Tools 2022 (C++ workload)
CMake 3.16 or newer
Building
cmake -B build -S .
cmake --build build

The Qt path is set in CMakeLists.txt via CMAKE_PREFIX_PATH — adjust it if Qt is installed elsewhere. The executable is written to out/.

To run outside the development environment, deploy the Qt dependencies next to the executable:

deploy.bat
Known limitations
Latency is around 30 ms, limited by Qt Multimedia running on WASAPI in shared mode. Moving to RtAudio or PortAudio (WASAPI exclusive or ASIO) is the planned fix; only the audio output layer would need to change.
Square and saw waveforms are not band-limited, so they alias at high notes.
Roadmap
Low-pass and high-pass filters per voice, with resonance
Full ADSR envelope
Detune between oscillators
Master EQ
