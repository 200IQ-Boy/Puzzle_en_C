#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "game.h"
#include "game_aux.h"
#include <string.h>

int test_dummy(){
    return EXIT_SUCCESS;
}


int game_width(game g) {
    uint i_next, j_next, size = 0;
    bool is_inside = game_get_ajacent_square(g, 0, 0, EAST, &i_next, &j_next);

    if (is_inside) {
       size += 1;

        while (game_get_ajacent_square(g, i_next, j_next, EAST, &i_next, &j_next)) {
            size += 1;
        }
    }

    if (size == 0) {
        return 0;
    } else {
        return size + 1;
    }
}

int game_height(game g) {
    uint i_next, j_next, size = 0;
    bool is_inside = game_get_ajacent_square(g, 0, 0, SOUTH, &i_next, &j_next);

    if (is_inside) {
       size += 1;

        while (game_get_ajacent_square(g, i_next, j_next, SOUTH, &i_next, &j_next)) {
            size += 1;
        }
    }

    if (size == 0) {
        return 0;
    } else {
        return size + 1;
    }
}


bool test_game_new_empty() {
    game g = game_new_empty();

    if (g == NULL) {
        game_delete(g);
        return false;
    }

    if (game_width(g)!=DEFAULT_SIZE ||game_height(g)!=DEFAULT_SIZE) {
        game_delete(g);
        return false;
    }

    for (int i = 0; i < DEFAULT_SIZE; i++) {
        for (int j = 0;j<DEFAULT_SIZE;j++){
            shape s= game_get_piece_shape(g,i,j);
            direction dir = game_get_piece_orientation(g,i,j);
            if (s!=EMPTY || dir!=NORTH) {
                game_delete(g);
                return false;
            }
        }
    }

    game_delete(g);
    return true;
}

bool test_game_new(){
    game g=game_new(NULL,NULL);
    game g2=game_new_empty();

    if (game_width(g) != DEFAULT_SIZE || game_height(g) != DEFAULT_SIZE) {
        game_delete(g);
        game_delete(g2);
        return false;
    }

    if(!game_equal(g, g2, false)) {
        game_delete(g);
        game_delete(g2);
        return false;
    }

    shape ts[25] = {0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4};
    direction td[25] = {0, 1, 2, 3, 0, 0, 1, 2, 3, 0, 0, 1, 2, 3, 0, 0, 1, 2, 3, 0, 0, 1, 2, 3, 0};

    game g3 = game_new(ts,td);

    if (game_width(g3) != DEFAULT_SIZE || game_height(g3) != DEFAULT_SIZE) {
        game_delete(g);
        game_delete(g2);
        game_delete(g3);
        return false;
    }

    for (int i = 0; i < DEFAULT_SIZE; i++) {
        for (int j = 0;j<DEFAULT_SIZE;j++){
            shape s= game_get_piece_shape(g3,i,j);
            direction dir = game_get_piece_orientation(g3,i,j);

            if (s != ts[i * DEFAULT_SIZE + j] || dir != td[i * DEFAULT_SIZE + j]) {
                game_delete(g);
                game_delete(g2);
                game_delete(g3);
                return false;
            }
        }
    }

    game g4 = game_new(NULL, td);

    if (game_width(g4) != DEFAULT_SIZE || game_height(g4) != DEFAULT_SIZE) {
        game_delete(g);
        game_delete(g2);
        game_delete(g3);
        game_delete(g4);
        return false;
    }

    for (int i = 0; i < DEFAULT_SIZE; i++) {
        for (int j = 0;j<DEFAULT_SIZE;j++){
            shape s= game_get_piece_shape(g4,i,j);
            direction dir = game_get_piece_orientation(g4,i,j);

            if (s != EMPTY || dir != td[i * DEFAULT_SIZE + j]) {
                game_delete(g);
                game_delete(g2);
                game_delete(g3);
                game_delete(g4);
                return false;
            }
        }
    }

    game g5 = game_new(ts, NULL);

    if (game_width(g5) != DEFAULT_SIZE || game_height(g5) != DEFAULT_SIZE) {
        game_delete(g);
        game_delete(g2);
        game_delete(g3);
        game_delete(g4);
        game_delete(g5);
        return false;
    }

    for (int i = 0; i < DEFAULT_SIZE; i++) {
        for (int j = 0;j<DEFAULT_SIZE;j++){
            shape s= game_get_piece_shape(g5,i,j);
            direction dir = game_get_piece_orientation(g5,i,j);

            if (s != ts[i * DEFAULT_SIZE + j] || dir != NORTH) {
                game_delete(g);
                game_delete(g2);
                game_delete(g3);
                game_delete(g4);
                game_delete(g5);
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

    shape ts[25] = {0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4};
    direction td[25] = {0, 1, 2, 3, 0, 0, 1, 2, 3, 0, 0, 1, 2, 3, 0, 0, 1, 2, 3, 0, 0, 1, 2, 3, 0};

    game g2=game_new(ts,td);
    game g3=game_copy(g2);

    if (game_width(g3) != DEFAULT_SIZE || game_height(g3) != DEFAULT_SIZE) {
        game_delete(g1);
        game_delete(g2);
        game_delete(g3);
        return false;
    }

    if (!game_equal(g3,g2,false) || !game_equal(g3, g2, false)) {
        game_delete(g1);
        game_delete(g2);
        game_delete(g3);
        return false;
    }

    game g4 = game_copy(g1);


    if (game_width(g4) != DEFAULT_SIZE || game_height(g4) != DEFAULT_SIZE) {
        game_delete(g1);
        game_delete(g2);
        game_delete(g3);
        game_delete(g4);
        return false;
    }

    if (!game_equal(g1,g4,false) || !game_equal(g1, g4, false)) {
        game_delete(g1);
        game_delete(g2);
        game_delete(g3);
        game_delete(g4);
        return false;
    }

    game_delete(g1);
    g1 = game_copy(g3);
    
    if (game_width(g1) != DEFAULT_SIZE || game_height(g1) != DEFAULT_SIZE) {
        game_delete(g1);
        game_delete(g2);
        game_delete(g3);
        game_delete(g4);
        return false;
    }

    game g5 = game_new_empty();
    if (game_equal(g1,g5,false) || game_equal(g1, g5, true)) {
        game_delete(g1);
        game_delete(g2);
        game_delete(g3);
        game_delete(g4);
        game_delete(g5);
        return false;
    }

    game_delete(g1);
    game_delete(g2);
    game_delete(g3);
    game_delete(g4);
    game_delete(g5);

    return true;
}

bool test_game_equal(){
    game g1=game_new_empty();
    game g2=game_new_empty();

    bool t1=game_equal(g1,g2,true);
    bool t2=game_equal(g1,g2,false);

    shape ts[25] = {0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4};
    direction td[25] = {0, 1, 2, 3, 0, 0, 1, 2, 3, 0, 0, 1, 2, 3, 0, 0, 1, 2, 3, 0, 0, 1, 2, 3, 0};

    game g3=game_new(ts,td);

    bool t3=game_equal(g1,g3,true);
    bool t4 = game_equal(g1, g3, false);

    td[0]=1;
    game g4 = game_new(ts, td);
    bool t5 = game_equal(g3, g4, false);
    bool t6 = game_equal(g3, g4, true);

    td[0] = 0;
    ts[0] = 1;
    game g5 = game_new(ts, td);
    bool t7 = game_equal(g3, g5, false);
    bool t8 = game_equal(g3, g5, true);

    td[0] = 2;
    ts[0] = 2;
    game g6 = game_new(ts, td);
    bool t9 = game_equal(g3, g6, false);
    bool t10 = game_equal(g3, g6, true);

    game g7 = game_new(ts, td);
    bool t11 = game_equal(g6, g7, false);
    bool t12 = game_equal(g6, g7, true);


    game_delete(g1);
    game_delete(g2);
    game_delete(g3);
    game_delete(g4);
    game_delete(g5);
    game_delete(g6);
    game_delete(g7);

    return t1 && t2 && !t3 && !t4 && !t5 && t6 && !t7 && !t8 && !t9 && !t10 && t11 && t12;
}

bool test_game_delete(){
    game g = game_default();
    game *pg = &g;
    game_delete(g);

    if (g != NULL || game_equal(game_new_empty(), *pg, false))
        return true;
    return false;
}

bool test_game_set_piece_shape(){
    game g1=game_new_empty();
    for (int i=0;i<NB_SHAPES;i++){
        game_set_piece_shape(g1,0,0,i);
        if(game_get_piece_shape(g1,0,0)!=i) {
            game_delete(g1);
            return false;
        }
    }
    game_delete(g1);
    return true;
}

bool test_game_set_piece_orientation(){
    game g1=game_new_empty();
    for (int i=0;i<NB_DIRS;i++){
        game_set_piece_orientation(g1,0,0,i);
        if(game_get_piece_orientation(g1,0,0)!=i) {
            game_delete(g1);
            return false;
        }
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