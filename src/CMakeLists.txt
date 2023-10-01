set(BINARY ${CMAKE_PROJECT_NAME})

file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true *.hpp *.cpp)

set(SOURCES ${SOURCES})

add_executable(${BINARY}_run ${SOURCES})

add_library(${BINARY}_lib STATIC ${SOURCES}
        Handlers/Interface/MapObserver.hpp
        Handlers/Interface/Subject.hpp
        MapGenerator/DefaultLevels/DefaultLevelGenerator.cpp
        MapGenerator/DefaultLevels/DefaultLevelGenerator.hpp
        Profiler/Timer.cpp
        Profiler/Timer.hpp
        Event/MovementEvents/Key.cpp
        Event/MovementEvents/Key.hpp
        Event/MovementEvents/Door.cpp
        Event/MovementEvents/Door.hpp)