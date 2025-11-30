cmake_minimum_required(VERSION 3.14)
project(DungeonEditor)

set(CMAKE_CXX_STANDARD 17)

# Находим GoogleTest
find_package(GTest REQUIRED)

# Основная программа
add_executable(dungeon_editor 
    src/main.cpp 
    src/npcs.cpp 
    src/factory.cpp 
    src/observer.cpp 
    src/dungeon_editor.cpp
)

# Включаем директории
target_include_directories(dungeon_editor PUBLIC ${CMAKE_SOURCE_DIR}/include)

# Тесты
add_executable(dungeon_tests 
    tests/test_dungeon.cpp 
    src/npcs.cpp 
    src/factory.cpp 
    src/observer.cpp 
    src/dungeon_editor.cpp
)

target_include_directories(dungeon_tests PUBLIC ${CMAKE_SOURCE_DIR}/include)

# Линкуем GoogleTest
target_link_libraries(dungeon_tests GTest::gtest GTest::gtest_main)

# Включаем тесты
include(GoogleTest)
gtest_discover_tests(dungeon_tests)
