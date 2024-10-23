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
add_test(test_tyao_game_get_piece_shape ./game_test_tyao test_game_get_piece_shape )
add_test(test_tyao_game_get_piece_orientation ./game_test_tyao test_game_get_piece_orientation)
add_test(test_tyao_game_play_move ./game_test_tyao test_game_play_move)
add_test(test_tyao_game_won ./game_test_tyao test_game_won)
add_test(test_tyao_game_reset_orientation ./game_test_tyao test_game_reset_orientation)
add_test(test_tyao_game_print ./game_test_tyao test_game_print)
add_test(test_tyao_game_shuffle_orientation ./game_test_tyao test_game_shuffle_orientation)