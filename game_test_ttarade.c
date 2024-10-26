#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "game.h"
#include "game_aux.h"

int test_dummy() {
    return EXIT_SUCCESS;
}

// Fonctions auxiliaires
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

// Tests

// Test de la fonction game_default
bool test_game_default() {
    game g = game_default();

    if (g == NULL) {
        game_delete(g);
        return false;
    }

    if (game_width(g) != DEFAULT_SIZE || game_height(g) != DEFAULT_SIZE) {
        game_delete(g);
        return false;
    }

    for (uint i = 0; i < game_height(g); i++) {
        for (uint j = 0; j < game_width(g); j++) {
            if (game_get_piece_shape(g, i, j) < 0 || game_get_piece_shape(g, i, j) >= NB_SHAPES || game_get_piece_orientation(g, i, j) < 0 || game_get_piece_orientation(g, i, j) >= NB_DIRS) {
                game_delete(g);
                return false;
            }
        }
    }

    game_delete(g);

    return true;
}

// Test de la fonction game_default_solution
bool test_game_default_solution() {
    game g = game_default();
    game gs = game_default_solution();

    if (gs == NULL) {
        game_delete(g);
        game_delete(gs);
        return false;
    }

    if (!game_won(gs)) {
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


    for (uint i = 0; i < game_height(gs); i++) {
        for (uint j = 0; j < game_width(gs); j++) {
            if (game_get_piece_shape(gs, i, j) < 0 || game_get_piece_shape(gs, i, j) >= NB_SHAPES || game_get_piece_orientation(gs, i, j) < 0 || game_get_piece_orientation(gs, i, j) >= NB_DIRS) {
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

// Test de la fonction game_get_ajacent_square
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

    // Cas limites
    if (game_get_ajacent_square(g, 0, 0, NORTH, &i_next, &j_next)) {
        game_delete(g);
        return false;
    }

    if (game_get_ajacent_square(g, 0, 0, WEST, &i_next, &j_next)) {
        game_delete(g);
        return false;
    }

    if (game_get_ajacent_square(g, game_height(g) - 1, game_width(g) - 1, SOUTH, &i_next, &j_next)) {
        game_delete(g);
        return false;
    }

    if (game_get_ajacent_square(g, game_height(g) - 1, game_width(g) - 1, EAST, &i_next, &j_next)) {
        game_delete(g);
        return false;
    }

    if (game_get_ajacent_square(g, 0, game_width(g) - 1, NORTH, &i_next, &j_next)) {
        game_delete(g);
        return false;
    }

    if (game_get_ajacent_square(g, 0, game_width(g) - 1, EAST, &i_next, &j_next)) {
        game_delete(g);
        return false;
    }

    if (game_get_ajacent_square(g, game_height(g) - 1, 0, SOUTH, &i_next, &j_next)) {
        game_delete(g);
        return false;
    }

    if (game_get_ajacent_square(g, game_height(g) - 1, 0, WEST, &i_next, &j_next)) {
        game_delete(g);
        return false;
    }

    for (int i = 1; i < game_height(g) - 1; i++) {
        if (game_get_ajacent_square(g, i, 0, WEST, &i_next, &j_next)) {
            game_delete(g);
            return false;
        }

        if (game_get_ajacent_square(g, i, game_width(g) - 1, EAST, &i_next, &j_next)) {
            game_delete(g);
            return false;
        }
    }

    for (int j = 1; j < game_width(g) - 1; j++) {
        if (game_get_ajacent_square(g, 0, j, NORTH, &i_next, &j_next)) {
            game_delete(g);
            return false;
        }

        if (game_get_ajacent_square(g, game_height(g) - 1, j, SOUTH, &i_next, &j_next)) {
            game_delete(g);
            return false;
        }
    }

    game_delete(g);

    return true;
}

// Test de la fonction game_has_half_edge
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

// Test de la fonction game_check_edge
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
    game g = game_default();
    if (game_is_connected(g)) {
        game_delete(g);
        return false;
    }

    game gs = game_default_solution();
    if (!game_is_connected(gs)) {
        game_delete(g);
        game_delete(gs);
        return false;
    }

    game ge = game_new_empty();
    if (!game_is_connected(ge)) {
        game_delete(g);
        game_delete(gs);
        game_delete(ge);
        return false;
    }

    game_play_move(gs, 0, 0, 1);

    if (game_is_connected(gs)) {
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

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <test_name>\n", argv[0]);
        return EXIT_FAILURE;
    }

    fprintf(stderr, "=> Start test \"%s\"\n", argv[1]);

    bool ok = false;

    if (strcmp("dummy", argv[1]) == 0) {
       return test_dummy();
    } else if (strcmp("test_game_default", argv[1]) == 0) {
        ok = test_game_default();
    } else if (strcmp("test_game_default_solution", argv[1]) == 0) {
        ok = test_game_default_solution();
    } else if (strcmp("test_game_get_ajacent_square", argv[1]) == 0) {
        ok = test_game_get_ajacent_square();
    } else if (strcmp("test_game_has_half_edge", argv[1]) == 0) {
        ok = test_game_has_half_edge();
    } else if (strcmp("test_game_check_edge", argv[1]) == 0) {
        ok = test_game_check_edge();
    } else if (strcmp("test_game_is_well_paired", argv[1]) == 0) {
        ok = test_game_is_well_paired();
    } else if (strcmp("test_game_is_connected", argv[1]) == 0) {
        ok = test_game_is_connected();
    } else {
        fprintf(stderr, "=> Error: test \"%s\" not found!\n", argv[1]);
        return EXIT_FAILURE;
    }
    
    if (ok) {
        fprintf(stderr, "=> Test \"%s\": SUCCESS\n", argv[1]);
        return EXIT_SUCCESS;
    } else {
        fprintf(stderr, "=> Test \"%s\": FAILURE\n", argv[1]);
        return EXIT_FAILURE;
    }
}