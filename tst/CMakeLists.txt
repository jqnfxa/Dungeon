set(BINARY ${CMAKE_PROJECT_NAME}_tst)

file(GLOB_RECURSE TEST_SOURCES LIST_DIRECTORIES false *.hpp *.cpp)

set(SOURCES ${TEST_SOURCES})

add_executable(${BINARY} ${TEST_SOURCES}
        PlayerTest.cpp
        CellTest.cpp
        MapTest.cpp
        PlayerHandlerTest.cpp
        SpikesTest.cpp
        PotionTest.cpp
        RandomMineTest.cpp
        SmallMapTest.cpp
        RandomLevelGenTest.cpp
        MediumMapTest.cpp)

add_test(NAME ${BINARY} COMMAND ${BINARY})

target_link_libraries(${BINARY} PUBLIC ${CMAKE_PROJECT_NAME}_lib gtest)