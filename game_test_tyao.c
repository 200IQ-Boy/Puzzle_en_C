#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "game.h"
#include "game_aux.h"

int test_dummy() {
    return EXIT_SUCCESS;
}

bool test_game_get_piece_shape(){
    game g = game_new_empty();
    if(game_get_piece_shape(g,0,0) != EMPTY){
        game_delete(g);
        return false;
    }
    shape ts[]={0,0,0,0,0,1,1,1,1,1,2,2,2,2,2,3,3,3,3,3,4,4,4,4,4};
    direction td[] = {0,1,2,3,1,1,3,2,1,2,3,2,3,2,2,1,2,3,2,1,2,2,3,2,0};
    game g3=game_new(ts,td);
    for(int i = 0;i < 5;i++){
        for(int j = 0 ;j < 5;j++){
            if(game_get_piece_shape(g3,i,j) != i){
                game_delete(g);
                game_delete(g3);
                return false;
            }
        }
    }
    game_delete(g);
    game_delete(g3);
    return true;
}

bool test_game_get_piece_orientation(){
    game g = game_new_empty();
    if(game_get_piece_orientation(g,0,0) != NORTH) {
        game_delete(g);
        return false;
    }
    shape ts[]={0,0,0,0,0,1,1,1,1,1,2,2,2,2,2,3,3,3,3,3,4,4,4,4,4};
    direction td[] = {0,1,2,3,3,0,1,2,3,3,0,1,2,3,3,0,1,2,3,3,0,1,2,3,3};
    game g3=game_new(ts,td);
    for(int i = 0;i<5;i++){
        for(int j = 0 ;j < 4;j++){
            if(game_get_piece_orientation(g3,i,j) != j){
                game_delete(g);
                game_delete(g3);
                return false;
            }
        }
    }
    game_delete(g);
    game_delete(g3);
    return true;
}
bool test_game_play_move() {
    shape ts[]={0,1,2,3,4,0,0,0,0,2,0,0,3,0,0,0,0,0,1,0,3,3,2,1,0};
    direction td[] = {0, 0, 0, 0, 0, 1, 3, 2, 1, 2, 3, 2, 3, 2, 2, 1, 2, 3, 2, 1, 2, 2, 3, 2, 0};
    game g=game_new(ts,td);
    for(int i = 0;i<4;i++){
        for(int j = 0;j<5;j++){
            game_play_move(g,0,j,i);
            if(game_get_piece_orientation(g,0,j) != i){
                game_delete(g);
                return false;
            }
            game_play_move(g,0,j,-i);
            if(game_get_piece_orientation(g,0,j) != 0){
                game_delete(g);
                return false;
            }
        }
    }
    game_play_move(g,0,0,-5);
    if(game_get_piece_orientation(g,0,0) != 3){
        game_delete(g);
        return false;
    }
    game_delete(g);
    return true;
}
bool test_game_won(){
    game g1 = game_new_empty();
    game g2=game_default();
    game g3 = game_default_solution();
    bool test1 = (game_won(g1));
    bool test2 = (!game_won(g2));
    bool test3 = game_won(g3);
    game_delete(g1);
    game_delete(g2);
    game_delete(g3);
    return test1 && test2 && test3;
}
bool test_game_reset_orientation(){
    shape ts[]={0,0,0,0,1,1,1,1,2,2,2,2,3,3,3,3,4,4,4,4,3,3,2,1,0};
    direction td[] = {0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 2, 2, 3, 2, 0};
    game g=game_new(ts,td);
    game g1 = game_default();
    game g2 = game_default_solution();
    game g3 = game_new_empty();
    game_reset_orientation(g);
    game_reset_orientation(g1);
    game_reset_orientation(g2);
    game_reset_orientation(g3);
    for(int i = 0;i<5;i++){
        for(int j = 0;j<5;j++){
            if(game_get_piece_orientation(g1,i,j) != 0){
                game_delete(g);
                game_delete(g1);
                game_delete(g2);
                game_delete(g3);
                return false;
            }
            if(game_get_piece_orientation(g2,i,j) != 0){
                game_delete(g);
                game_delete(g1);
                game_delete(g2);
                game_delete(g3);
                return false;
            }
            if(game_get_piece_orientation(g3,i,j) != 0){
                game_delete(g);
                game_delete(g1);
                game_delete(g2);
                game_delete(g3);
                return false;
            }
            if(game_get_piece_orientation(g,i,j) != 0){
                game_delete(g);
                game_delete(g1);
                game_delete(g2);
                game_delete(g3);
                return false;
            }
        }
    }
    game_delete(g);
    game_delete(g1);
    game_delete(g2);
    game_delete(g3);
    return true;
}
bool test_game_print(){
    game g1 = game_default();
    game_print(g1);
    game_delete(g1);
    game g2 = game_new_empty();
    game_print(g2);
    game_delete(g2);
    shape ts[]={0,0,0,0,1,1,1,1,2,2,2,2,3,3,3,3,4,4,4,4,3,3,2,1,0};
    direction td[] = {0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 2, 2, 3, 2, 0};
    game g3=game_new(ts,td);
    game_print(g3);
    game_delete(g3);
    return true;
}
bool test_game_shuffle_orientation(){
    shape ts[]={0,0,0,0,1,1,1,1,2,2,2,2,3,3,3,3,4,4,4,4,3,3,2,1,0,2};
    direction td[] = {0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 2, 2, 3, 2, 0};
    game g=game_new(ts,td);
    game_shuffle_orientation(g);

    direction dprec = game_get_piece_orientation(g, 0, 0);
    bool all_same = true;
    for (int i = 0; i < DEFAULT_SIZE; i++) {
        for (int j = 0; j < DEFAULT_SIZE; j++) {
            if (i == 0 && j == 0) {
                continue;
            }

            if (game_get_piece_orientation(g, i, j) != dprec) {
                all_same = false;
                break;
            } else {
                dprec = game_get_piece_orientation(g, i, j);
            }
        }
    }

    if (all_same) {
        game_delete(g);
        return false;
    }

    int ecart = game_get_piece_orientation(g,0,0) - td[0];
    for(int i = 0;i < 5; i++){
        for(int j = 0; j<5;j++){
            if(game_get_piece_orientation(g,i,j) - td[i*5+j] != ecart){
                game_delete(g);
                return true;
            }
        }
    }
    game_shuffle_orientation(g);
    ecart = game_get_piece_orientation(g,0,0) - td[0];
    for(int i = 0;i < 5; i++){
        for(int j = 0; j<5;j++){
            if(game_get_piece_orientation(g,i,j) - td[i*5+j] != ecart){
                game_delete(g);
                return true;
            }
        }
    }

    game g1 = game_default();
    game g2 = game_new_empty();
    game g3 = game_default_solution();
    game_shuffle_orientation(g1);
    game_shuffle_orientation(g2);
    game_shuffle_orientation(g3);
    game_delete(g);
    game_delete(g1);
    game_delete(g2);
    game_delete(g3);
    return false;
}

void usage(int argc, char *argv[])
{
  fprintf(stderr, "Usage: %s <testname> [<...>]\n", argv[0]);
  exit(EXIT_FAILURE);
}

int main(int argc , char * argv[]) {
    if (argc == 1)
        usage(argc, argv);
    fprintf(stderr, "=> Start test \"%s\"\n", argv[1]);
    bool ok = false;
    if(strcmp("dummy",argv[1]) == 0)
        return test_dummy();
    else if(strcmp("test_game_get_piece_shape",argv[1]) == 0)
        ok = test_game_get_piece_shape();
    else if(strcmp("test_game_get_piece_orientation",argv[1]) == 0)
        ok = test_game_get_piece_orientation();
    else if(strcmp("test_game_play_move",argv[1]) == 0)
        ok = test_game_play_move();
    else if(strcmp("test_game_won",argv[1]) == 0)
        ok = test_game_won();
    else if(strcmp("test_game_reset_orientation",argv[1]) == 0)
        ok = test_game_reset_orientation();
    else if(strcmp("test_game_print",argv[1]) == 0)
        ok = test_game_print();
    else if(strcmp("test_game_shuffle_orientation",argv[1]) == 0)
        ok = test_game_shuffle_orientation();
    else
    {
        fprintf(stderr, "Error: test \"%s\" not found!\n", argv[1]);
        exit(EXIT_FAILURE);
    }
    if (ok)
    {
        fprintf(stderr, "Test \"%s\" finished: SUCCESS\n", argv[1]);
        return EXIT_SUCCESS;
    }
    else
    {
        fprintf(stderr, "Test \"%s\" finished: FAILURE\n", argv[1]);
        return EXIT_FAILURE;
    }
}