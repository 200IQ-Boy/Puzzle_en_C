#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "game.h"
#include "game_aux.h"

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

direction opposite(direction d) {
    switch (d) {
        case NORTH:
            return SOUTH;
        case EAST:
            return WEST;
        case SOUTH:
            return NORTH;
        case WEST:
            return EAST;
        default:
            return NB_DIRS;
    }
}

direction clockwise(direction d) {
    switch (d) {
        case NORTH:
            return EAST;
        case EAST:
            return SOUTH;
        case SOUTH:
            return WEST;
        case WEST:
            return NORTH;
        default:
            return NB_DIRS;
    }
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

bool test_game_default() {
    game g = game_default();

    direction td[25] = {3, 0, 3, 0, 2, 2, 3, 0, 1, 1, 1, 0, 3, 3, 1, 2, 2, 0, 3, 0, 1, 3, 2, 1, 2};
    shape ts[25] = {3, 1, 1, 3, 1, 4, 4, 4, 4, 4, 1, 1, 4, 1, 2, 1, 4, 4, 3, 2, 1, 4, 1, 1, 1};

    if (g == NULL) {
        game_delete(g);
        return false;
    }

    if (game_width(g) != DEFAULT_SIZE || game_height(g) != DEFAULT_SIZE) {
        game_delete(g);
        return false;
    }

    for (int i = 0; i < DEFAULT_SIZE; i++) {
        for (int j = 0; j < DEFAULT_SIZE; j++) {
            if (game_get_piece_shape(g, i, j) != ts[i * DEFAULT_SIZE + j] || game_get_piece_orientation(g, i, j) != td[i * DEFAULT_SIZE + j]) {
                game_delete(g);
                return false;
            }
        }
    }

    game_delete(g);

    return true;
}

bool test_game_default_solution() {
    game g = game_default();
    game gs = game_default_solution();

    direction td[25] = {1, 3, 1, 2, 2, 1, 2, 2, 0, 3, 0, 0, 1, 3, 2, 1, 2, 0, 2, 0, 1, 0, 3, 0, 0};
    shape ts[25] = {3, 1, 1, 3, 1, 4, 4, 4, 4, 4, 1, 1, 4, 1, 2, 1, 4, 4, 3, 2, 1, 4, 1, 1, 1};

    if (gs == NULL) {
        game_delete(g);
        game_delete(gs);
        return false;
    }

    if (!game_won(gs) || !game_is_well_paired(gs) || !game_is_connected(gs)) {
        game_delete(g);
        game_delete(gs);
        return false;
    }

    if (!game_equal(g, gs, true)) {
        game_delete(g);
        game_delete(gs);
        return false;
    }

    if (game_width(gs) != DEFAULT_SIZE || game_height(gs) != DEFAULT_SIZE) {
        game_delete(g);
        game_delete(gs);
        return false;
    }


    for (int i = 0; i < DEFAULT_SIZE; i++) {
        for (int j = 0; j < DEFAULT_SIZE; j++) {
            if (game_get_piece_shape(gs, i, j) != ts[i * DEFAULT_SIZE + j] || game_get_piece_orientation(gs, i, j) != td[i * DEFAULT_SIZE + j]) {
                game_delete(g);
                game_delete(gs);
                return false;
            }
        }
    }

    game_delete(g);
    game_delete(gs);

    return true;
}

bool test_game_get_ajacent_square() {
    game g = game_default();
    uint i_next = 0, j_next = 0;

    if (!game_get_ajacent_square(g, 0, 0, EAST, &i_next, &j_next) || i_next != 0 || j_next != 1) {
        game_delete(g);
        return false;
    }

    if (!game_get_ajacent_square(g, 0, 0, SOUTH, &i_next, &j_next) || i_next != 1 || j_next != 0) {
        game_delete(g);
        return false;
    }

    if (!game_get_ajacent_square(g, 1, 0, NORTH, &i_next, &j_next) || i_next != 0 || j_next != 0) {
        game_delete(g);
        return false;
    }

    if (!game_get_ajacent_square(g, 0, 1, WEST, &i_next, &j_next) || i_next != 0 || j_next != 0) {
        game_delete(g);
        return false;
    }

    // Tester avec NULL

    // Cas limites
    if (game_get_ajacent_square(g, 0, 0, NORTH, &i_next, &j_next)) {
        game_delete(g);
        return false;
    }

    if (game_get_ajacent_square(g, 0, 0, WEST, &i_next, &j_next)) {
        game_delete(g);
        return false;
    }

    if (game_get_ajacent_square(g, DEFAULT_SIZE - 1, DEFAULT_SIZE - 1, SOUTH, &i_next, &j_next)) {
        game_delete(g);
        return false;
    }

    if (game_get_ajacent_square(g, DEFAULT_SIZE - 1, DEFAULT_SIZE - 1, EAST, &i_next, &j_next)) {
        game_delete(g);
        return false;
    }

        if (game_get_ajacent_square(g, 0, DEFAULT_SIZE - 1, NORTH, &i_next, &j_next)) {
        game_delete(g);
        return false;
    }

    if (game_get_ajacent_square(g, 0, DEFAULT_SIZE - 1, EAST, &i_next, &j_next)) {
        game_delete(g);
        return false;
    }

    if (game_get_ajacent_square(g, DEFAULT_SIZE - 1, 0, SOUTH, &i_next, &j_next)) {
        game_delete(g);
        return false;
    }

    if (game_get_ajacent_square(g, DEFAULT_SIZE - 1, 0, WEST, &i_next, &j_next)) {
        game_delete(g);
        return false;
    }

    for (int i = 1; i < DEFAULT_SIZE - 1; i++) {
        if (game_get_ajacent_square(g, i, 0, WEST, &i_next, &j_next)) {
            game_delete(g);
            return false;
        }

        if (game_get_ajacent_square(g, i, DEFAULT_SIZE - 1, EAST, &i_next, &j_next)) {
            game_delete(g);
            return false;
        }
    }

    for (int j = 1; j < DEFAULT_SIZE - 1; j++) {
        if (game_get_ajacent_square(g, 0, j, NORTH, &i_next, &j_next)) {
            game_delete(g);
            return false;
        }

        if (game_get_ajacent_square(g, DEFAULT_SIZE - 1, j, SOUTH, &i_next, &j_next)) {
            game_delete(g);
            return false;
        }
    }

    game_delete(g);

    return true;
}

bool test_game_has_half_edge() {
    game g = game_default();

    for (int shape = 0; shape < NB_SHAPES; shape++) {
        for (int orientation1 = 0; orientation1 < NB_DIRS; orientation1++) {
            game_set_piece_shape(g, 0, 0, shape);
            game_set_piece_orientation(g, 0, 0, orientation1);

            for (int orientation2 = 0; orientation2 < NB_DIRS; orientation2++) {
                if (shape == EMPTY) {
                    if (game_has_half_edge(g, 0, 0, orientation2)) {
                        game_delete(g);
                        return false;
                    }
                } else if (shape == ENDPOINT) {
                    if (orientation1 == orientation2) {
                        if (!game_has_half_edge(g, 0, 0, orientation2)) {
                            game_delete(g);
                            return false;
                        }
                    } else {
                        if (game_has_half_edge(g, 0, 0, orientation2)) {
                            game_delete(g);
                            return false;
                        }
                    }
                } else if (shape == SEGMENT) {
                    if (orientation1 == orientation2 || orientation2 == opposite(orientation1)) {
                        if (!game_has_half_edge(g, 0, 0, orientation2)) {
                            game_delete(g);
                            return false;
                        }
                    } else {
                        if (game_has_half_edge(g, 0, 0, orientation2)) {
                            game_delete(g);
                            return false;
                        }
                    }
                } else if (shape == CORNER) {
                    if (orientation1 == orientation2 || orientation2 == clockwise(orientation1)) {
                        if (!game_has_half_edge(g, 0, 0, orientation2)) {
                            game_delete(g);
                            return false;
                        }
                    } else {
                        if (game_has_half_edge(g, 0, 0, orientation2)) {
                            game_delete(g);
                            return false;
                        }
                    }
                } else if (shape == TEE) {
                    if (orientation2 == opposite(orientation1)) {
                        if (game_has_half_edge(g, 0, 0, orientation2)) {
                            game_delete(g);
                            return false;
                        }
                    } else {
                        if (!game_has_half_edge(g, 0, 0, orientation2)) {
                            game_delete(g);
                            return false;
                        }
                    }
                } else {
                    game_delete(g);
                    return false;
                }
            }
        }
    }

    game_delete(g);

    return true;
}

bool test_game_check_edge() {
    game g = game_default();

    for (int shape1 = 0; shape1 < NB_SHAPES; shape1++) {
        for (int shape2 = 0; shape2 < NB_SHAPES; shape2++) {
            for (int orientation1 = 0; orientation1 < NB_DIRS; orientation1++) {
                for (int orientation2 = 0; orientation2 < NB_DIRS; orientation2++) {
                    game_set_piece_shape(g, 2, 2, shape1);
                    game_set_piece_orientation(g, 2, 2, orientation1);

                    uint i_next = 0; uint j_next = 0;
                    bool is_inside = game_get_ajacent_square(g, 2, 2, orientation2, &i_next, &j_next);
                    game_set_piece_shape(g, i_next, j_next, shape2);

                    if (is_inside) {
                        edge_status status = game_check_edge(g, 2, 2, orientation2);
                        if (status == MATCH) {
                            if (!(game_has_half_edge(g, 2, 2, orientation2) && game_has_half_edge(g, i_next, j_next, opposite(orientation2)))) {
                                game_delete(g);
                                return false;
                            }
                        } else if (status == MISMATCH) {
                            if (!(game_has_half_edge(g, 2, 2, orientation2) ^ game_has_half_edge(g, i_next, j_next, opposite(orientation2)))) {
                                game_delete(g);
                                return false;
                            }
                        } else if (status == NOEDGE) {
                            if (!(!game_has_half_edge(g, 2, 2, orientation2) && !game_has_half_edge(g, i_next, j_next, opposite(orientation2)))) {
                                game_delete(g);
                                return false;
                            }
                        }
                    } else {
                        game_delete(g);
                        return false;
                    }
                }
            }
        }
    }

    game_delete(g);

    return true;
}

bool test_game_is_well_paired() {
    game g = game_default();
    if (game_is_well_paired(g)) {
        game_delete(g);
        return false;
    }

    game gs = game_default_solution();
    if (!game_is_well_paired(gs)) {
        game_delete(g);
        game_delete(gs);
        return false;
    }

    game ge = game_new_empty();
    if (!game_is_well_paired(ge)) {
        game_delete(g);
        game_delete(gs);
        game_delete(ge);
        return false;
    }

    for (int i = 0; i < game_height(gs); i++) {
        for (int j = 0; j < game_width(gs); j++) {
            if (i == 0 && j == 0) {
                direction p[2] = {EAST, SOUTH};

                for (int d = 0; d < 2; d++) {
                    if (game_check_edge(gs, i, j, p[d]) == MISMATCH) {
                        game_delete(g);
                        game_delete(gs);
                        game_delete(ge);
                        return false;
                    }
                }
            } else if (i == game_height(gs) - 1 && j == game_width(gs) - 1) {
                direction p[2] = {NORTH, WEST};

                for (int d = 0; d < 2; d++) {
                    if (game_check_edge(gs, i, j, p[d]) == MISMATCH) {
                        game_delete(g);
                        game_delete(gs);
                        game_delete(ge);
                        return false;
                    }
                }
            } else if (i == game_height(gs) - 1 && j == 0) {
                direction p[2] = {NORTH, EAST};

                for (int d = 0; d < 2; d++) {
                    if (game_check_edge(gs, i, j, p[d]) == MISMATCH) {
                        game_delete(g);
                        game_delete(gs);
                        game_delete(ge);
                        return false;
                    }
                }
            } else if (i == 0 && j == game_width(gs) - 1) {
                direction p[2] = {SOUTH, WEST};

                for (int d = 0; d < 2; d++) {
                    if (game_check_edge(gs, i, j, p[d]) == MISMATCH) {
                        game_delete(g);
                        game_delete(gs);
                        game_delete(ge);
                        return false;
                    }
                }
            } else if (i == 0) {
                direction p[3] = {EAST, SOUTH, WEST};

                for (int d = 0; d < 3; d++) {
                    if (game_check_edge(gs, i, j, p[d]) == MISMATCH) {
                        game_delete(g);
                        game_delete(gs);
                        game_delete(ge);
                        return false;
                    }
                }
            } else if (j == 0) {
                direction p[3] = {NORTH, EAST, SOUTH};

                for (int d = 0; d < 3; d++) {
                    if (game_check_edge(gs, i, j, p[d]) == MISMATCH) {
                        game_delete(g);
                        game_delete(gs);
                        game_delete(ge);
                        return false;
                    }
                }
            } else if (i == game_height(gs) - 1) {
                direction p[3] = {NORTH, EAST, WEST};

                for (int d = 0; d < 3; d++) {
                    if (game_check_edge(gs, i, j, p[d]) == MISMATCH) {
                        game_delete(g);
                        game_delete(gs);
                        game_delete(ge);
                        return false;
                    }
                }
            } else if (j == game_width(gs) - 1) {
                direction p[3] = {NORTH, SOUTH, WEST};

                for (int d = 0; d < 3; d++) {
                    if (game_check_edge(gs, i, j, p[d]) == MISMATCH) {
                        game_delete(g);
                        game_delete(gs);
                        game_delete(ge);
                        return false;
                    }
                }
            } else {
                direction p[4] = {NORTH, EAST, SOUTH, WEST};

                for (int d = 0; d < 4; d++) {
                    if (game_check_edge(gs, i, j, p[d]) == MISMATCH) {
                        game_delete(g);
                        game_delete(gs);
                        game_delete(ge);
                        return false;
                    }
                }
            }
        }
    }

    game_play_move(gs, 0, 0, 1);

    if (game_is_well_paired(gs)) {
        game_delete(g);
        game_delete(gs);
        game_delete(ge);
        return false;
    }

    game_delete(g);
    game_delete(gs);
    game_delete(ge);

    return true;
}

bool test_game_is_connected() {
    // On test avec une partie par défaut
    game g = game_default();
    if (game_is_connected(g)) {
        game_delete(g);
        return false;
    }

    // On test avec la solution de la partie par défaut
    game gs = game_default_solution();
    if (!game_is_connected(gs)) {
        game_delete(g);
        game_delete(gs);
        return false;
    }

    // On test avec une partie vide
    game ge = game_new_empty();
    if (!game_is_connected(ge)) {
        game_delete(g);
        game_delete(gs);
        game_delete(ge);
        return false;
    }

    // On test avec une partie qui se base sur la partie gagnante, mais on bouge une pièce
    // Désormais on a une pièce isolée, et en plus une pièce pointe vers une pièce qui n'existe pas
    game_play_move(gs, 0, 0, 1);

    if (game_is_connected(gs)) {
        game_delete(g);
        game_delete(gs);
        game_delete(ge);
        return false;
    }

    // Cette fois la partie est connectée, mais on a une pièce qui pointe vers une pièce qui n'existe pas
    game_set_piece_shape(gs, 0, 0, TEE);

    if (game_is_connected(gs)) {
        game_delete(g);
        game_delete(gs);
        game_delete(ge);
        return false;
    }

    // On retourne à la solution de la partie par défaut
    game_set_piece_shape(gs, 0, 0, CORNER);
    game_play_move(gs, 0, 0, -1);

    if (!game_is_connected(gs)) {
        game_delete(g);
        game_delete(gs);
        game_delete(ge);
        return false;
    }

    // Une pièce isolée
    game_set_piece_orientation(gs, 4, 0, NORTH);
    game_set_piece_shape(gs, 4, 1, CORNER);

    if (game_is_connected(gs)) {
        game_delete(g);
        game_delete(gs);
        game_delete(ge);
        return false;
    }

    game_delete(gs);
    gs = game_default_solution();

    // Un cycle isolé
    game_set_piece_shape(gs, 0, 0, CORNER);
    game_set_piece_orientation(gs, 0, 0, EAST);

    game_set_piece_shape(gs, 0, 1, CORNER);
    game_set_piece_orientation(gs, 0, 1, SOUTH);

    game_set_piece_shape(gs, 1, 0, CORNER);
    game_set_piece_orientation(gs, 1, 0, NORTH);

    game_set_piece_shape(gs, 1, 1, CORNER);
    game_set_piece_orientation(gs, 1, 1, WEST);

    game_set_piece_shape(gs, 1, 2, CORNER);
    game_set_piece_orientation(gs, 1, 2, EAST);

    if (game_is_connected(gs)) {
        game_delete(g);
        game_delete(gs);
        game_delete(ge);
        return false;
    }

    game_delete(gs);
    gs = game_default_solution();

    // Un cycle connecté
    game_set_piece_shape(gs, 3, 0, CORNER);
    game_set_piece_orientation(gs, 3, 0, EAST);

    game_set_piece_shape(gs, 4, 0, CORNER);
    game_set_piece_orientation(gs, 4, 0, NORTH);

    if (!game_is_connected(gs)) {
        game_delete(g);
        game_delete(gs);
        game_delete(ge);
        return false;
    }

    // Une partie, séparée en deux
    shape ts1[DEFAULT_SIZE * DEFAULT_SIZE] = {CORNER, SEGMENT, CORNER, CORNER, CORNER, SEGMENT, CORNER, CORNER, SEGMENT, SEGMENT, SEGMENT, SEGMENT, CORNER, CORNER, SEGMENT, SEGMENT, SEGMENT, SEGMENT, SEGMENT, SEGMENT, CORNER, CORNER, CORNER, TEE, CORNER};
    direction td1[DEFAULT_SIZE * DEFAULT_SIZE] = {EAST, EAST, SOUTH, EAST, SOUTH, NORTH, NORTH, WEST, NORTH, NORTH, NORTH, NORTH, EAST, WEST, NORTH, NORTH, NORTH, NORTH, NORTH, NORTH, NORTH, WEST, NORTH, NORTH, WEST};

    game gnew1 = game_new(ts1, td1);

    if (game_is_connected(gnew1)) {
        game_delete(g);
        game_delete(gs);
        game_delete(ge);
        game_delete(gnew1);
        return false;
    }

    game_set_piece_orientation(gnew1, 1, 1, EAST);

    if (game_is_connected(gnew1)) {
        game_delete(g);
        game_delete(gs);
        game_delete(ge);
        game_delete(gnew1);
        return false;
    }

    shape ts2[DEFAULT_SIZE * DEFAULT_SIZE] = {CORNER, SEGMENT, SEGMENT, SEGMENT, CORNER, SEGMENT, CORNER, TEE, CORNER, SEGMENT, SEGMENT, SEGMENT, SEGMENT, SEGMENT, SEGMENT, SEGMENT, CORNER, TEE, CORNER, SEGMENT, CORNER, SEGMENT, SEGMENT, SEGMENT, CORNER};
    direction td2[DEFAULT_SIZE * DEFAULT_SIZE] = {EAST, EAST, EAST, EAST, SOUTH, NORTH, EAST, SOUTH, SOUTH, NORTH, NORTH, NORTH, NORTH, NORTH, NORTH, NORTH, NORTH, NORTH, WEST, NORTH, NORTH, WEST, WEST, WEST, WEST};

    game gnew2 = game_new(ts2, td2);

    if (game_is_connected(gnew2)) {
        game_delete(g);
        game_delete(gs);
        game_delete(ge);
        game_delete(gnew1);
        game_delete(gnew2);
        return false;
    }

    game_set_piece_shape(gnew2, 1, 1, TEE);
    game_set_piece_orientation(gnew2, 1, 1, EAST);

    if (game_is_connected(gnew2)) {
        game_delete(g);
        game_delete(gs);
        game_delete(ge);
        game_delete(gnew1);
        game_delete(gnew2);
        return false;
    }

    game_set_piece_shape(gnew2, 0, 1, TEE);
    game_set_piece_orientation(gnew2, 0, 1, SOUTH);

    if (!game_is_connected(gnew2)) {
        game_delete(g);
        game_delete(gs);
        game_delete(ge);
        game_delete(gnew1);
        game_delete(gnew2);
        return false;
    }

    game_delete(g);
    game_delete(gs);
    game_delete(ge);
    game_delete(gnew1);
    game_delete(gnew2);

    return true;
}

bool test_game_new_empty() {
    game g1 = game_new_empty();

    if (g1 == NULL ) {
        game_delete(g1);
        return false;
    }

    if (game_width(g1)!=DEFAULT_SIZE ||game_height(g1)!=DEFAULT_SIZE) {
        game_delete(g1);
        return false;
    }

    for (int i = 0; i < DEFAULT_SIZE; i++) {
        for (int j = 0;j<DEFAULT_SIZE;j++){
            shape s= game_get_piece_shape(g1,i,j);
            direction dir = game_get_piece_orientation(g1,i,j);
            if (s!=EMPTY || dir!=NORTH) {
                game_delete(g1);
                return false;
            }
        }
    }

    game_delete(g1);
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

    shape ts[25] = {0, 1, 2, 3, 1, 0, 0, 1, 3, 2, 0, 1, 2, 1, 1, 0, 0, 2, 3, 3, 1, 1, 2, 0, 0};
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

    game g6 = game_new(ts, NULL);

    if (game_width(g6) != DEFAULT_SIZE || game_height(g6) != DEFAULT_SIZE) {
        game_delete(g);
        game_delete(g2);
        game_delete(g3);
        game_delete(g4);
        game_delete(g6);
        return false;
    }

    for (int i = 0; i < DEFAULT_SIZE; i++) {
        for (int j = 0;j<DEFAULT_SIZE;j++){
            shape s= game_get_piece_shape(g6,i,j);
            direction dir = game_get_piece_orientation(g6,i,j);

            if (s != ts[i * DEFAULT_SIZE + j] || dir != NORTH) {
                game_delete(g);
                game_delete(g2);
                game_delete(g3);
                game_delete(g4);
                game_delete(g6);
                return false;
            }
        }
    }

    game_delete(g);
    game_delete(g2);
    game_delete(g3);
    game_delete(g4);
    game_delete(g6);

    return true;
}

bool test_game_copy(){
    game g1=game_new_empty();

    shape ts[25] = {0, 1, 2, 3, 1, 0, 0, 1, 3, 2, 0, 1, 2, 1, 1, 0, 0, 2, 3, 3, 1, 1, 2, 0, 0};
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
    game_play_move(g2,0,0,1);
    if (game_equal(g3,g2,false)) {
        game_delete(g1);
        game_delete(g2);
        game_delete(g3);
        return false;
    }
    game_play_move(g3,0,0,2);
    if (game_equal(g3,g2,false)) {
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
    bool ta = game_equal(g3, g6, true);

    game g7 = game_new(ts, td);

    bool tb = game_equal(g6, g7, false);

    bool tc = game_equal(g6, g7, true);

    g1 = game_default();

    g2 = game_default_solution();

    bool tf = game_equal(g1,g2,false);

    bool te = game_equal(g1,g2,true);

    game_delete(g1);
    game_delete(g2);
    game_delete(g3);
    game_delete(g4);
    game_delete(g5);
    game_delete(g6);
    game_delete(g7);

    return t1 && t2 && !t3 && !t4 && !t5 && t6 && !t7 && !t8 && !t9 && !ta && tb && tc && !tf && te;
}

/*bool test_game_delete(){
    game g = game_default();
    game *pg = &g;
    game_delete(g);

    if (game_equal(game_default(), *pg, false))
        return true;
    return false;
}*/

bool test_game_set_piece_shape(){
    game g=game_new_empty();
    for (int i=0;i<NB_SHAPES;i++){
        game_set_piece_shape(g,0,0,i);
        if(game_get_piece_shape(g,0,0)!=i) {
            game_delete(g);
            return false;
        }
    }
    game_delete(g);
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

int main(int argc , char * argv[]) {
    if (argc == 1)
        usage(argc, argv);
    fprintf(stderr, "=> Start test \"%s\"\n", argv[1]);
    bool ok = false;
    if(strcmp("test_game_get_piece_shape",argv[1]) == 0)
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
    else if (strcmp("test_game_default", argv[1]) == 0) 
        ok = test_game_default();
    else if (strcmp("test_game_default_solution", argv[1]) == 0) 
        ok = test_game_default_solution();
    else if (strcmp("test_game_get_ajacent_square", argv[1]) == 0) 
        ok = test_game_get_ajacent_square();
    else if (strcmp("test_game_has_half_edge", argv[1]) == 0) 
        ok = test_game_has_half_edge();
    else if (strcmp("test_game_check_edge", argv[1]) == 0) 
        ok = test_game_check_edge();
    else if (strcmp("test_game_is_well_paired", argv[1]) == 0) 
        ok = test_game_is_well_paired();
    else if (strcmp("test_game_is_connected", argv[1]) == 0) 
        ok = test_game_is_connected();
    else if(strcmp("test_game_new_empty",argv[1]) == 0)
        ok = test_game_new_empty();
    else if(strcmp("test_game_new",argv[1]) == 0)
        ok = test_game_new();
    else if(strcmp("test_game_copy",argv[1]) == 0)
        ok = test_game_copy();
    else if(strcmp("test_game_equal",argv[1]) == 0)
        ok = test_game_equal();
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