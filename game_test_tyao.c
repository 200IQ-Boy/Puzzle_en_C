#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "game.h"
#include "game_aux.h"

int test_dummy() {
    return EXIT_SUCCESS;
}

bool test_game_get_piece_shape(){
    game g = game_new_empty();
    bool test1 = (game_get_piece_shape(g,0,0) == EMPTY);
    shape ts[]={0,1,2,3,4,0,0,0,0,2,0,0,3,0,0,0,0,0,1,0,3,3,2,1,0,2};
    game g3=game_new(ts,NULL);
    for(int i = 0;i<5;i++){
        if(game_get_piece_shape(g,0,i) != i){
            return false;
        }
    }
    game_delete(g);
    game_delete(g3);
    return test1;
}

bool test_game_get_piece_orientation(){
    game g = game_new_empty();
    bool test1 = (test_game_get_piece_orientation(g,0,0) == NORTH);
    shape ts[]={1,1,2,3,4,0,0,0,0,2,0,0,3,0,0,0,0,0,1,0,3,3,2,1,0,2};
    direction td[] = {0, 1, 2, 3, 1, 1, 3, 2, 1, 2, 3, 2, 3, 2, 2, 1, 2, 3, 2, 1, 2, 2, 3, 2, 0};
    game g3=game_new(ts,td);
    for(int i = 0;i<4;i++){
        if(game_get_piece_orientation(g,0,i) != i){
            return false;
        }
    }
    game_delete(g);
    game_delete(g3);
    return test1;
}
bool test_game_play_move() {
    shape ts[]={1,1,2,3,4,0,0,0,0,2,0,0,3,0,0,0,0,0,1,0,3,3,2,1,0,2};
    direction td[] = {0, 1, 2, 3, 1, 1, 3, 2, 1, 2, 3, 2, 3, 2, 2, 1, 2, 3, 2, 1, 2, 2, 3, 2, 0};
    game g=game_new(ts,td);
    game_play_move(g,0,0,3);
    if(game_get_piece_orientation(g,0,0) != 3){
        return false;
    }
    game_play_move(g,0,0,-3);
    if(game_get_piece_orientation(g,0,0) != 0){
        return false;
    }
    game_play_move(g,0,0,5);
    if(game_get_piece_orientation(g,0,0) != 1){
        return false;
    }
    game_delete(g);
    return true;
}
bool test_game_won(){
    game g1 = game_new_empty();
    game g2=game_default();
    game g3 = game_default_solution();
    return !game_won(g1) && !game_won(g2) && game_won(g3);
}
bool test_game_reset_orientation(){
    shape ts[]={0,0,0,0,1,1,1,1,2,2,2,2,3,3,3,3,4,4,4,4,3,3,2,1,0,2};
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
    shape ts[]={0,0,0,0,1,1,1,1,2,2,2,2,3,3,3,3,4,4,4,4,3,3,2,1,0,2};
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

int main(int argc , char * argv[]) {
    if(argc != 2){
        fprintf(stderr,"usage: ./game_test_tyao dummy\n");
        return EXIT_FAILURE;
    }
    char * dummy = argv[1];
    char * p = "dummy";
    while( *p != '\0' && *dummy != '\0' && (*dummy == *p)){
        dummy++;
        p++;
    }
    if(*p != *dummy){
        fprintf(stderr,"usage: ./game_test_tyao dummy\n");
        return EXIT_FAILURE;
    }
    return test_dummy();
}