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

    srand(100);

    t_map map = createMapFromFile("maps/example1.map");

    printf("Map created with dimensions %d x %d\n", map.y_max, map.x_max);
    for (int i = 0; i < map.y_max; i++) {
        for (int j = 0; j < map.x_max; j++)
        {
            printf("%d ", map.soils[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    int* moves_selected;
    int phase_movements_number = EXECUTED_MOVES_NUMBER;

    t_localisation start_loc;
    start_loc.pos.x = 4;
    start_loc.pos.y = 6;
    start_loc.ori = NORTH;
    
    t_localisation current_loc = start_loc;

    printf("Position de depart generee :\nPosition Y : %d, Postion X : %d\nOrientation : %s\n\n", current_loc.pos.y, current_loc.pos.x, orientation_strings[current_loc.ori]);

    int on_phase = 1;
    int phase_number = 1;

    while (on_phase) {
        printf("\n\nPhase %d :\n\n", phase_number);

        moves_selected = moves_selections();

        printf("Mouvements selectionnes :\n");
        for (int i = 0; i < SELECTED_MOVES_NUMBER; i++) {
            printf("- %s\n", _moves[moves_selected[i]]);
        }
        printf("\n\n");

        double execution_time_tree = 0.0;
        clock_t begin_build = clock();
        
        t_tree tree;
        buildTree(&tree, moves_selected, current_loc, map);

        clock_t end_build = clock();
        execution_time_tree = ((double)(end_build-begin_build))/CLOCKS_PER_SEC;
        
        if (tree.root != NULL) {
            /*
            display_full_tree(&tree);
            //*/
        }
        printf("Temps d'execution de la phase de construction de l'arbre : %.3f secondes\n", execution_time_tree);

        double execution_time_best_moves = 0.0;
        clock_t begin_best_moves = clock();
        
        int reg_activated;

        if (map.soils[current_loc.pos.y][current_loc.pos.x] == REG) {
            reg_activated = 1;
        } else {
            reg_activated = 0;
        }
        
        int* best_moves_executed = best_moves(&tree, phase_movements_number);
        
        clock_t end_best_moves = clock();
        execution_time_best_moves = ((double)(end_best_moves - begin_best_moves)) / CLOCKS_PER_SEC;
        printf("Temps d'execution pour calculer le chemin de la racine vers la feuille : %.3f secondes\n\n", execution_time_best_moves);
        
        if (best_moves_executed == NULL) {
            printf("La meilleure suite de mouvements n'a pas ete trouvee.\n");
            on_phase = 0;
        } else {
            printf("Liste des meilleurs mouvements :\n");
            for (int moves_index = 0; moves_index < phase_movements_number; moves_index++) {
                current_loc = move_exec(current_loc, best_moves_executed[moves_index], map, &reg_activated);
                printf("%s\n", _moves[best_moves_executed[moves_index]]);

                if (map.soils[current_loc.pos.x][current_loc.pos.y] == 0) {
                    printf("Le rover a retrouve la station ! Bien joue !");
                    on_phase = 0;
                    break;
                }
            }
        }

        if (reg_activated) {
            phase_movements_number = EXECUTED_MOVES_NUMBER - 1;
            reg_activated = 0;
        } else {
            phase_movements_number = EXECUTED_MOVES_NUMBER;
        }

        phase_number++;
    }

    return 0;
}
