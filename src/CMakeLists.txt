
add_library(src)

target_sources(src
    PRIVATE
        card.cpp
        resource_manager.cpp
        hand.cpp
        playmat.cpp
    
    PUBLIC
        FILE_SET HEADERS
        FILES
            card.hpp
            hand.hpp
            playmat.hpp
            resource_manager.hpp
)

target_link_libraries(src PRIVATE raylib)