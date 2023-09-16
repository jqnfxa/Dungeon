cmake_minimum_required(VERSION 3.26)
project(DungeonGame)

set(CMAKE_CXX_STANDARD 20)

add_executable(DungeonGame main.cpp
        Entities/Player/Player.cpp
        Entities/Player/Player.hpp
        Entities/Interface/EntityInterface.hpp
        Math/Vector2.hpp
        Entities/Player/Player.cpp
        Handlers/PlayerHandler/PlayerHandler.cpp
        Handlers/PlayerHandler/PlayerHandler.hpp
        Movement/Direction.hpp
        Movement/Direction.cpp)
