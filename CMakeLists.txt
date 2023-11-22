cmake_minimum_required(VERSION 3.26)
project(DungeonGame)

set(CMAKE_CXX_STANDARD 23)

include_directories(src/game_client)
include_directories(src/features)

add_subdirectory(src)
add_subdirectory(tst)
add_subdirectory(lib/googletest)
