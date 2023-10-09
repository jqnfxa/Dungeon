set(BINARY ${CMAKE_PROJECT_NAME})

file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true *.hpp *.cpp)

set(SOURCES ${SOURCES})

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

add_executable(${BINARY}_run ${SOURCES})

target_link_libraries(${BINARY}_run sfml-graphics sfml-system)

add_library(${BINARY}_lib STATIC ${SOURCES}
        Game/State/PlayingState.cpp
        Game/State/PlayingState.hpp
        Game/State/TerinateState.cpp
        Game/State/TerinateState.hpp
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
)