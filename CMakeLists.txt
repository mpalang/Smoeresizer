cmake_minimum_required(VERSION 3.16)
project(Smoeresizer VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "C:/tools/Qt/6.11.1/msvc2022_64")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/out")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/out/debug")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/out")

find_package(Qt6 REQUIRED COMPONENTS Widgets Multimedia)

set(SOURCES
    src/main.cpp
    src/gui/styling.h
    src/gui/styling.cpp

    src/gui/mainwindow.cpp
    src/gui/mainwindow.h

    src/gui/widgets.cpp
    src/gui/widgets.h

    src/gui/panels/oscilloscope.cpp
    src/gui/panels/oscilloscope.h
    src/gui/panels/oscipanel.cpp
    src/gui/panels/oscipanel.h
    src/gui/panels/effectpanel.cpp
    src/gui/panels/effectpanel.h
    src/gui/panels/keyboard.cpp
    src/gui/panels/keyboard.h
    src/gui/panels/frequencyfilterpanel.cpp
    src/gui/panels/frequencyfilterpanel.h
    src/gui/panels/masterpanel.cpp
    src/gui/panels/masterpanel.h

    src/sound_engine/oscillator.cpp
    src/sound_engine/oscillator.h
    src/sound_engine/note.h
    src/sound_engine/voice.h
    src/sound_engine/voice.cpp
    src/sound_engine/synthengine.h
    src/sound_engine/synthengine.cpp
    src/audio/audiosource.cpp
    src/audio/audiosource.h

)
add_executable(Smoeresizer ${SOURCES})

target_include_directories(Smoeresizer PRIVATE
    src
    src/gui
    src/gui/panels
    src/sound_engine
    src/audio
)

target_link_libraries(Smoeresizer PRIVATE Qt6::Widgets Qt6::Multimedia)

if(WIN32)
    set_target_properties(Smoeresizer PROPERTIES WIN32_EXECUTABLE ON)
endif()