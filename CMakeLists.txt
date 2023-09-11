cmake_minimum_required(VERSION 3.26)
project(Dungeon)

set(CMAKE_CXX_STANDARD 20)

add_executable(Dungeon src/main.cpp
        src/Entities/Player.cpp
        src/Entities/Player.hpp
        src/WorldManager.cpp
        src/WorldManager.hpp
        src/Entities/Bot.cpp
        src/Entities/Bot.hpp
        src/Map.cpp
        src/Map.hpp)
