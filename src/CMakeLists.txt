set(BINARY ${CMAKE_PROJECT_NAME})

file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true *.hpp *.cpp)

set(SOURCES ${SOURCES})

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

add_executable(${BINARY}_run ${SOURCES})

target_link_libraries(${BINARY}_run sfml-graphics sfml-system)

add_library(${BINARY}_lib STATIC ${SOURCES}
        Game/GameState.cpp
        Game/GameState.hpp
        Command/System/TriggerPlayMenu.cpp
        Command/System/TriggerPlayMenu.hpp
        Command/Gameplay/ChangeGameDifficulty.cpp
        Command/Gameplay/ChangeGameDifficulty.hpp
        Command/Gameplay/ChangeGameSize.cpp
        Command/Gameplay/ChangeGameSize.hpp
        Command/Gameplay/CreateSession.cpp
        Command/Gameplay/CreateSession.hpp
        Command/Gameplay/RestartSession.cpp
        Command/Gameplay/RestartSession.hpp
        Input/SFML/SFMLInput.cpp
        Input/SFML/SFMLInput.hpp
        Command/Gameplay/Resume.cpp
        Command/Gameplay/Resume.hpp
        GUI/Window.cpp
        Command/Factory/CommandFactory.cpp
        Command/Factory/CommandFactory.hpp)