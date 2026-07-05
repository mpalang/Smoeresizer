cmake_minimum_required(VERSION 3.15)

project(Smoeresizer VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(C:/tools/JUCE JUCE)

juce_add_plugin(Smoeresizer
    COMPANY_NAME "SmoereApps"
    IS_SYNTH TRUE
    NEEDS_MIDI_INPUT TRUE
    NEEDS_MIDI_OUTPUT FALSE
    PLUGIN_MANUFACTURER_CODE MyCo
    PLUGIN_CODE MySy
    FORMATS VST3 Standalone
)

target_sources(Smoeresizer PRIVATE
    Source/Main.cpp
)

target_link_libraries(Smoeresizer PRIVATE
    juce::juce_audio_utils
    juce::juce_dsp
)