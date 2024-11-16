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

    t_localisation start_loc = generate_start_loc(map.x_max, map.y_max);
    
    t_tree tree;
    buildTree(&tree, moves_selected, start_loc, map);

    if (tree.root != NULL) {
        display_full_tree(&tree);
    }


    int* best_moves_executed = best_moves(&tree, phase_movements_number);

    printf("Liste des meilleurs mouvements :\n");
    for (int moves_index = 0; moves_index < phase_movements_number; moves_index++) {
        //if pos == 0
        printf("%s\n", _moves[best_moves_executed[moves_index]]);
    }


    // Libération de la mémoire de l'arbre (à implémenter si nécessaire)

    return 0;
}
