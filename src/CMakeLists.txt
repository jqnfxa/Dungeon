set(BINARY ${CMAKE_PROJECT_NAME})

file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true *.hpp *.cpp)

set(SOURCES ${SOURCES})

add_executable(${BINARY}_run ${SOURCES})

add_library(${BINARY}_lib STATIC ${SOURCES}
        Event/Interface/EventInterface.hpp
        Event/Spikes.cpp
        Event/Spikes.hpp
        Handlers/Interface/HandlerInterface.hpp
        Handlers/MapHandler/MapHandler.cpp
        Handlers/MapHandler/MapHandler.hpp
        Event/Potion.cpp
        Event/Potion.hpp
        Event/RandomMine.cpp
        Event/RandomMine.hpp
        MapGenerator/Level_1/GenerateLevel1.cpp
        MapGenerator/Level_1/GenerateLevel1.hpp)