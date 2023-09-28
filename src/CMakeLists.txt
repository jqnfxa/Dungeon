set(BINARY ${CMAKE_PROJECT_NAME})

file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true *.hpp *.cpp)

set(SOURCES ${SOURCES})

add_executable(${BINARY}_run ${SOURCES})

add_library(${BINARY}_lib STATIC ${SOURCES}
        Event/Interface/EventInterface.hpp
        Event/NegativeEvents/Spikes.cpp
        Event/NegativeEvents/Spikes.hpp
        Handlers/Interface/HandlerInterface.hpp
        Handlers/MapHandler/MapHandler.cpp
        Handlers/MapHandler/MapHandler.hpp
        Event/PositiveEvents/Potion.cpp
        Event/PositiveEvents/Potion.hpp
        Event/MovementEvents/RandomMine.cpp
        Event/MovementEvents/RandomMine.hpp
        Random/Random.cpp
        Random/Random.hpp
        MapGenerator/RandomLevelGen/Generator.cpp
        MapGenerator/RandomLevelGen/Generator.hpp
        MapGenerator/MediumMap/MediumMap.cpp
        MapGenerator/MediumMap/MediumMap.hpp
        MapGenerator/SmallMap/SmallMap.cpp
        MapGenerator/SmallMap/SmallMap.hpp
        Event/PositiveEvents/Star.cpp
        Event/PositiveEvents/Star.hpp
        Event/PositiveEvents/ShieldKit.cpp
        Event/PositiveEvents/ShieldKit.hpp
)