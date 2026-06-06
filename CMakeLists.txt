cmake_minimum_required(VERSION 3.20)

if(WIN32)
    set(CMAKE_C_COMPILER "C:/raylib/w64devkit/bin/gcc.exe")
    set(CMAKE_CXX_COMPILER "C:/raylib/w64devkit/bin/g++.exe")
endif()

project(apex-game)

set(CMAKE_CXX_STANDARD 17)

add_executable(apex-game
    main.cpp
    card.cpp
    resource_manager.cpp
    hand.cpp
)

if(WIN32)
    target_include_directories(apex-game PRIVATE C:/raylib/raylib/src)
    target_link_libraries(apex-game PRIVATE
        C:/raylib/raylib/src/libraylib.a
        opengl32
        gdi32
        winmm
    )
elseif(APPLE)
    find_package(raylib REQUIRED)
    target_link_libraries(apex-game PRIVATE
        raylib
        "-framework OpenGL"
        "-framework Cocoa"
        "-framework IOKit"
        "-framework CoreAudio"
        "-framework CoreVideo"
    )
endif()
