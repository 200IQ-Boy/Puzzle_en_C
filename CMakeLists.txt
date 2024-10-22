link_directories(${CMAKE_SOURCE_DIR})

cmake_minimum_required(VERSION 3.3)

project(game_text C)

include(CTest)
enable_testing()

set(CMAKE_C_FLAGS "-std=c99 -Wall -g")

add_executable(game_text game_text.c)
add_executable(game_test_tyao game_test_tyao.c)

target_link_libraries(game_text game00-macos)
target_link_libraries(game_test_tyao game00-macos)

add_test(test_tyao_dummy ./game_test_tyao dummy)