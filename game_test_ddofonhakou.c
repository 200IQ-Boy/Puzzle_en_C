#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "game.h"
#include "game_aux.h"
#include <string.h>

int test_dummy(){
    return EXIT_SUCCESS;
}

bool test_game_new_empty() {
    game g = game_new_empty();

    if (g == NULL) {
        return false;
    }

    for (int i = 0; i < DEFAULT_SIZE; i++) {
        for (int j = 0;j<DEFAULT_SIZE;j++){
            shape s= game_get_piece_shape(g,i,j);
            direction dir = game_get_piece_orientation(g,i,j);
            if (s!=EMPTY || dir!=NORTH)
                return false;

        }
    }
    game_delete(g);
    return true;
}

bool test_game_new(){
    game g=game_new(NULL,NULL);
    game g2=game_new_empty();
    if(!game_equal(g, g2, false))
        return false;

    shape ts[] = {0, 1, 2, 3, 1, 1, 4, 2, 1, 2, 3, 4, 3, 4, 2, 1, 2, 3, 2, 1, 2, 2, 3, 2, 4};
    direction td[] = {0, 1, 2, 3, 1, 1, 3, 2, 1, 2, 3, 2, 3, 2, 2, 1, 2, 3, 2, 1, 2, 2, 3, 2, 0};

    game g3 = game_new(ts,td);

    for (int i = 0; i < DEFAULT_SIZE; i++) {
        for (int j = 0;j<DEFAULT_SIZE;j++){
            shape s= game_get_piece_shape(g3,i,j);
            direction dir = game_get_piece_orientation(g3,i,j);

            if (s != ts[i * DEFAULT_SIZE + j] || dir != td[i * DEFAULT_SIZE + j]) {
                return false;
            }
        }
    }

    game g4 = game_new(NULL, td);

    for (int i = 0; i < DEFAULT_SIZE; i++) {
        for (int j = 0;j<DEFAULT_SIZE;j++){
            shape s= game_get_piece_shape(g4,i,j);
            direction dir = game_get_piece_orientation(g4,i,j);

            if (s != EMPTY || dir != td[i * DEFAULT_SIZE + j]) {
                return false;
            }
        }
    }

    game g5 = game_new(ts, NULL);

    for (int i = 0; i < DEFAULT_SIZE; i++) {
        for (int j = 0;j<DEFAULT_SIZE;j++){
            shape s= game_get_piece_shape(g5,i,j);
            direction dir = game_get_piece_orientation(g5,i,j);

            if (s != ts[i * DEFAULT_SIZE + j] || dir != NORTH) {
                return false;
            }
        }
    }

    game_delete(g);
    game_delete(g2);
    game_delete(g3);
    game_delete(g4);
    game_delete(g5);
    return true;
}

bool test_game_copy(){
    game g1=game_new_empty();
    shape ts[]={0, 1, 2, 3, 1, 1, 4, 2, 1, 2, 3, 4, 3, 4, 2, 1, 2, 3, 2, 1, 2, 2, 3, 2, 4};
    direction td[]= {0, 1, 2, 3, 1, 1, 3, 2, 1, 2, 3, 2, 3, 2, 2, 1, 2, 3, 2, 1, 2, 2, 3, 2, 0};
    game g2=game_new(ts,td);
    game g3=game_copy(g2);
    if (!game_equal(g3,g2,false))
        return false;

    g1=game_copy(g3);
    if(game_equal(g1,game_new_empty(),false))
        return false;
    game_delete(g1);
    game_delete(g2);
    game_delete(g3);
    return true;
}

bool test_game_equal(){
    game g1=game_new_empty();
    game g2=game_new_empty();

    bool t1=game_equal(g1,g2,true);
    bool t2=game_equal(g1,g2,false);

    shape ts[]={1,0,2,0,0,0,0,0,2,0,0,3,0,0,0,0,0,1,0,3,3,2,1,0,2};
    direction td[]={1,0,2,0,1,0,1,0,2,0,1,0,3,0,1,0,2,0,3,0,1,0,2,1,1};
    game g3=game_new(ts,td);
    bool t3=game_equal(g1,g3,true);
    ts[0]=0;
    td[0]=1;
    bool t4=game_equal(g1,g3,false);
    game_delete(g1);
    game_delete(g2);
    game_delete(g3);
    return t1 && t2 && !t3 && !t4 ;
}

bool test_game_delete(){
    game g = game_default();
    game *pg = &g;
    game_delete(g);

    if (game_equal(game_new_empty(), *pg, false))
        return true;
    return false;
}

bool test_game_set_piece_shape(){
    game g1=game_new_empty();
    for (int i=0;i<=4;i++){
        game_set_piece_shape(g1,0,0,i);
        if(game_get_piece_shape(g1,0,0)!=i)
            return false;
    }
    game_delete(g1);
    return true;
}

bool test_game_set_piece_orientation(){
    game g1=game_new_empty();
    for (int i=0;i<=3;i++){
        game_set_piece_orientation(g1,0,0,i);
        if(game_get_piece_orientation(g1,0,0)!=i)
            return false;
    }
    game_delete(g1);
    return true;
}

void usage(int argc, char *argv[])
{
  fprintf(stderr, "Usage: %s <testname> [<...>]\n", argv[0]);
  exit(EXIT_FAILURE);
}



int main (int argc, char *argv[]){
    if (argc == 1)
        usage(argc, argv);
    fprintf(stderr, "=> Start test \"%s\"\n", argv[1]);
    bool ok = false;
    if(strcmp("dummy",argv[1]) == 0)
        return test_dummy();
    else if(strcmp("test_game_new_empty",argv[1]) == 0)
        ok = test_game_new_empty();
    else if(strcmp("test_game_new",argv[1]) == 0)
        ok = test_game_new();
    else if(strcmp("test_game_copy",argv[1]) == 0)
        ok = test_game_copy();
    else if(strcmp("test_game_equal",argv[1]) == 0)
        ok = test_game_equal();
    else if(strcmp("test_game_delete",argv[1]) == 0)
        ok = test_game_delete();
    else if(strcmp("test_game_set_piece_shape",argv[1]) == 0)
        ok = test_game_set_piece_shape();
    else if(strcmp("test_game_set_piece_orientation",argv[1]) == 0)
        ok = test_game_set_piece_orientation();
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