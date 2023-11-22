set(BINARY ${CMAKE_PROJECT_NAME})

file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true *.hpp *.cpp)

set(SOURCES ${SOURCES})

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

add_executable(${BINARY}_run ${SOURCES})

target_link_libraries(${BINARY}_run sfml-graphics sfml-system)

add_library(${BINARY}_lib STATIC ${SOURCES})