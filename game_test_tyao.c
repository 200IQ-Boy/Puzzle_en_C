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
    shape ts[]={0,1,2,3,4,0,0,0,0,2,0,0,3,0,0,0,0,0,1,0,3,3,2,1,0};
    game g3=game_new(ts,NULL);
    for(int i = 0;i<5;i++){
        if(game_get_piece_shape(g3,0,i) != i){
            game_delete(g);
            game_delete(g3);
            return false;
        }
    }
    return true;
}

bool test_game_get_piece_orientation(){
    game g = game_new_empty();
    if(game_get_piece_orientation(g,0,0) != NORTH) {
        game_delete(g);
        return false;
    }
    shape ts[]={1,1,2,3,4,0,0,0,0,2,0,0,3,0,0,0,0,0,1,0,3,3,2,1,0};
    direction td[] = {0, 1, 2, 3, 1, 1, 3, 2, 1, 2, 3, 2, 3, 2, 2, 1, 2, 3, 2, 1, 2, 2, 3, 2, 0};
    game g3=game_new(ts,td);
    for(int i = 0;i<4;i++){
        if(game_get_piece_orientation(g3,0,i) != i){
            game_delete(g);
            game_delete(g3);
            return false;
        }
    }
    game_delete(g);
    game_delete(g3);
    return true;
}
bool test_game_play_move() {
    shape ts[]={0,1,2,3,4,0,0,0,0,2,0,0,3,0,0,0,0,0,1,0,3,3,2,1,0};
    direction td[] = {0, 1, 2, 3, 1, 1, 3, 2, 1, 2, 3, 2, 3, 2, 2, 1, 2, 3, 2, 1, 2, 2, 3, 2, 0};
    game g=game_new(ts,td);
    game_play_move(g,0,0,3);
    if(game_get_piece_orientation(g,0,0) != 3){
        game_delete(g);
        return false;
    }
    game_play_move(g,0,0,-3);
    if(game_get_piece_orientation(g,0,0) != 0){
        game_delete(g);
        return false;
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
    printf("g1 won: %d\n", game_won(g1)); 
    printf("g2 won: %d\n", game_won(g2));
    printf("g3 won: %d\n", game_won(g3));
    return (!game_won(g1)) && (!game_won(g2)) && game_won(g3);
}
bool test_game_reset_orientation(){
    shape ts[]={0,0,0,0,1,1,1,1,2,2,2,2,3,3,3,3,4,4,4,4,3,3,2,1,0};
    direction td[] = {0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 2, 2, 3, 2, 0};
    game g=game_new(ts,td);
    game_reset_orientation(g);
    for(int i = 0;i<5;i++){
        if(game_get_piece_orientation(g,0,i) != 0){
            return false;
        }
    }
    game_delete(g);
    return true;
}
bool test_game_print(){
    game g1 = game_default();
    game_print(g1);
    game_delete(g1);
    game g2 = game_new_empty();
    game_print(g2);
    game_delete(g1);
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
    int ecart = game_get_piece_orientation(g,0,0) - td[0];
    for(int i = 0;i < 5; i++){
        for(int j = 0; j<5;j++){
            if(game_get_piece_orientation(g,i,j) - td[i*5+j] != ecart){
                return true;
            }
        }
    }
    game_shuffle_orientation(g);
    for(int i = 0;i < 5; i++){
        for(int j = 0; j<5;j++){
            if(game_get_piece_orientation(g,i,j) - td[i*5+j] != ecart){
                return true;
            }
        }
    }
    game_delete(g);
    ecart = game_get_piece_orientation(g,0,0) - td[0];
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