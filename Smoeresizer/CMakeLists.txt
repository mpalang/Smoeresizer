cmake_minimum_required(VERSION 3.16)

project(Smoeresizer VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "C:/tools/Qt/6.11.1/msvc2022_64")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/bin")

find_package(Qt6 REQUIRED COMPONENTS Widgets Multimedia)

add_executable(Smoeresizer
    main.cpp
    mainwindow.cpp
    mainwindow.h
    oscillator.cpp
    oscillator.h
    audiosource.cpp
    audiosource.h
)

target_link_libraries(Smoeresizer PRIVATE Qt6::Widgets Qt6::Multimedia)

if(WIN32)
    set_target_properties(Smoeresizer PROPERTIES WIN32_EXECUTABLE ON)
endif()