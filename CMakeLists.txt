link_directories(${CMAKE_SOURCE_DIR})

cmake_minimum_required(VERSION 3.3)

project(game_text C)

include(CTest)
enable_testing()

set(CMAKE_C_FLAGS "-std=c99 -Wall -g")

add_executable(game_text game_text.c)
add_executable(game_test game_test.c)

target_link_libraries(game_text game00-macos-x86_64)
target_link_libraries(game_test game00-macos-x86_64)

add_test(test_game_get_piece_shape ./game_test test_game_get_piece_shape )
add_test(test_game_get_piece_orientation ./game_test test_game_get_piece_orientation)
add_test(test_game_play_move ./game_test test_game_play_move)
add_test(test_game_won ./game_test test_game_won)
add_test(test_game_reset_orientation ./game_test test_game_reset_orientation)
add_test(test_game_print ./game_test test_game_print)
add_test(test_game_shuffle_orientation ./game_test test_game_shuffle_orientation)
add_test(test_game_default ./game_test test_game_default)
add_test(test_game_default_solution ./game_test test_game_default_solution)
add_test(test_game_get_ajacent_square ./game_test test_game_get_ajacent_square)
add_test(test_game_has_half_edge ./game_test test_game_has_half_edge)
add_test(test_game_check_edge ./game_test test_game_check_edge)
add_test(test_game_is_well_paired ./game_test test_game_is_well_paired)
add_test(test_game_is_connected ./game_test test_game_is_connected)
add_test(test_game_new_empty ./game_test test_game_new_empty)
add_test(test_game_new ./game_test test_game_new)
add_test(test_game_copy ./game_test test_game_copy)
add_test(test_game_equal ./game_test test_game_equal)
add_test(test_game_set_piece_shape ./game_test test_game_set_piece_shape)
add_test(test_game_set_piece_orientation ./game_test test_game_set_piece_orientation)