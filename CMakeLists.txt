cmake_minimum_required(VERSION 3.20)

project(apex-game)


add_executable(apex-game)

target_sources(apex-game PRIVATE main.cpp)

target_link_libraries(apex-game PRIVATE src)

set(CMAKE_CXX_STANDARD 17)
target_compile_features(apex-game PRIVATE cxx_std_17)

if(WIN32)
    set(CMAKE_C_COMPILER "C:/raylib/w64devkit/bin/gcc.exe")
    set(CMAKE_CXX_COMPILER "C:/raylib/w64devkit/bin/g++.exe")
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
elseif(CMAKE_SYSTEM_NAME STREQUAL Linux)
    message("Linux Detected")
    target_link_libraries(apex-game
        PRIVATE
            raylib
    )
endif()


if(APEXGAME_ENABLE_IPO)
    include(CheckIPOSupported)
    check_ipo_supported(RESULT result OUTPUT output)
    if(result)
        message("IPO is supported, enabling IPO")
        set(CMAKE_INTERPROCEDURAL_OPTIMIZATION ON)
    else()
        message(WARNING "IPO is not supported: ${output}")
    endif()
endif()


include(GNUInstallDirs)

install(
    TARGETS apex-game
    DESTINATION ${CMAKE_INSTALL_BINDIR}
    FILE_SET HEADERS
)

install(
    DIRECTORY assets
    DESTINATION ${CMAKE_INSTALL_DATADIR}/assets
)

add_subdirectory(src)
