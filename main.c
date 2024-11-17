#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "map.h"
#include "moves.h"
#include "tree.h"
#include "loc.h"
#include "cost.h"
#include "draw.h"


/*
int main() {
    t_map map = createMapFromFile("maps/example1.map");
    printf("Map created with dimensions %d x %d\n", map.y_max, map.x_max);
    for (int i = 0; i < map.y_max; i++)
    {
        for (int j = 0; j < map.x_max; j++)
        {
            printf("%d ", map.soils[i][j]);
        }
        printf("\n");
    }
    // printf the costs, aligned left 5 digits
    for (int i = 0; i < map.y_max; i++)
    {
        for (int j = 0; j < map.x_max; j++)
        {
            printf("%-5d ", map.costs[i][j]);
        }
        printf("\n");
    }
    displayMap(map);
    return 0;
}
*/

int main() {
    srand(time(NULL));

    t_map map = createMapFromFile("maps/example1.map");

    int* moves_selected = moves_selections();
    int phase_movements_number = EXECUTED_MOVES_NUMBER;

    printf("Map created with dimensions %d x %d\n", map.y_max, map.x_max);
    for (int i = 0; i < map.y_max; i++) {
        for (int j = 0; j < map.x_max; j++)
        {
            printf("%d ", map.soils[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    t_localisation start_loc;
    start_loc.pos.x = 4;
    start_loc.pos.y = 6;
    start_loc.ori = NORTH;
    
    printf("Position de depart generee :\n Position Y : %d, Postion X : %d\nOrientation : %s\n\n", start_loc.pos.y, start_loc.pos.x, orientation_strings[start_loc.ori]);


    t_tree tree;
    buildTree(&tree, moves_selected, start_loc, map);

    if (tree.root != NULL) {
        //*
        display_full_tree(&tree);
        //*/
    }

    t_localisation current_loc = start_loc;

    int* best_moves_executed = best_moves(&tree, phase_movements_number);

    if (best_moves_executed == NULL) {
        printf("La meilleure suite de mouvements n'a pas ete trouvee.\n");
    } else {
        printf("Liste des meilleurs mouvements :\n");
        for (int moves_index = 0; moves_index < phase_movements_number; moves_index++) {
            current_loc = move(current_loc, best_moves_executed[moves_index]);
            printf("%s\n", _moves[best_moves_executed[moves_index]]);

            if (map.soils[current_loc.pos.x][current_loc.pos.y] == 0) {
                printf("Le rover a retrouve la station ! Bien joue !");
                break;
            }
        }
    }

    // Libération de la mémoire de l'arbre (à implémenter si nécessaire)

    return 0;
}
