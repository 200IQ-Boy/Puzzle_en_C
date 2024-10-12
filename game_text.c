#include <stdlib.h>
#include <stdio.h>
#include "game_aux.h"

int main(void) {
    game g = game_default();

    while (!game_won(g)) {
        game_print(g);
        
        char c;

        printf("? [h for help]\n");

        if (scanf(" %c", &c) == 1) {
            if (c == 'h') {
                printf("action: help\n");
                printf("- press 'c <i> <j>' to rotate piece clockwise in square (i,j)\n");
                printf("- press 'a <i> <j>' to rotate piece anti-clockwise in square (i,j)\n");
                printf("- press 'r' to shuffle game\n");
                printf("- press 'q' to quit\n");
            }

            else if (c == 'r') {
                printf("action: restart\n");
                game_shuffle_orientation(g);
            }

            else if (c == 'q') {
                printf("action: quit\n");
                break;
            }

            else if (c == 'c' || c == 'a') {
                int i, j;

                if (scanf("%d %d", &i, &j) == 2) {
                    if (c == 'c') {
                        printf("action: play move 'c' into square (%d,%d)\n", i, j);
                        game_play_move(g, i, j, 1);
                    }

                    else if (c == 'a') {
                        printf("action: play move 'a' into square (%d,%d)\n", i, j);
                        game_play_move(g, i, j, -1);
                    }
                }
            }

        }
        
    }

    game_print(g);

    if (game_won(g)) {
        printf("congratulation\n");
    } else {
        printf("shame\n");
    }

    return EXIT_SUCCESS;
}