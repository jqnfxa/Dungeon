set(BINARY ${CMAKE_PROJECT_NAME})

file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true *.hpp *.cpp)

set(SOURCES ${SOURCES})

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

add_executable(${BINARY}_run ${SOURCES})

target_link_libraries(${BINARY}_run sfml-graphics sfml-system)

add_library(${BINARY}_lib STATIC ${SOURCES}
        Game/State/PlayingState.cpp
        Game/State/PlayingState.hpp
        Game/State/TerminateState.cpp
        Game/State/TerminateState.hpp
        Game/State/MainMenuState.cpp
        Game/State/MainMenuState.hpp
        Game/State/SettingsState.cpp
        Game/State/SettingsState.hpp
        Game/State/PlayMenuState.cpp
        Game/State/PlayMenuState.hpp
        Game/State/HoldState.cpp
        Game/State/HoldState.hpp
        Game/State/WinState.cpp
        Game/State/WinState.hpp
        Game/State/LoseState.cpp
        Game/State/LoseState.hpp
        Draw/Interface/Interface.hpp
        Game/GameObserver.hpp
        Draw/Tracker.cpp
        Draw/Tracker.hpp
        Draw/SFML/SfmlRenderer.cpp
        Draw/SFML/SfmlRenderer.hpp
        Input/SFML/SfmlInput.cpp
        Input/SFML/SfmlInput.hpp
        Input/Base/InputClass.cpp
        Draw/SFML/SimpleMenu.cpp
        Draw/SFML/SimpleMenu.hpp
        Draw/SFML/Button.cpp
        Draw/SFML/Button.hpp
        Draw/SFML/RenderSlave.hpp
        Draw/SFML/GameRenderer.cpp
        Draw/SFML/GameRenderer.hpp
        Draw/SFML/PlayerStatistic.cpp
        Draw/SFML/PlayerStatistic.hpp
        Draw/SFML/Settings.cpp
        Draw/SFML/Settings.hpp
        Game/State/SizeChangeState.cpp
        Game/State/SizeChangeState.hpp
        Game/State/DifficultyChangeState.cpp
        Game/State/DifficultyChangeState.hpp
        Command/System/OpenSizeOptions.cpp
        Command/System/OpenSizeOptions.hpp
        Command/System/OpenDifficultyOptions.cpp
        Command/System/OpenDifficultyOptions.hpp
)