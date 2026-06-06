set(CMAKE_C_COMPILER "C:/raylib/w64devkit/bin/gcc.exe")
set(CMAKE_CXX_COMPILER "C:/raylib/w64devkit/bin/g++.exe")

cmake_minimum_required(VERSION 3.20)

project(apex-game)

set(CMAKE_CXX_STANDARD 17)

add_executable(apex-game
    main.cpp
    card.cpp
    resource_manager.cpp
    hand.cpp
)

target_include_directories(apex-game PRIVATE
    C:/raylib/raylib/src
)

target_link_libraries(apex-game PRIVATE
    C:/raylib/raylib/src/libraylib.a
    opengl32
    gdi32
    winmm
)