



#include <stdlib.h>
#include <time.h>
#include "draw.h"
#include "moves.h"


int move_draw(float* draw_table) {
    int move_type_index;

    int total_sum_proba = 0;
    for (move_type_index = 0; move_type_index < DIFFERENT_MOVES_NUMBER; move_type_index++) {
        total_sum_proba += (int)(draw_table[move_type_index] * 100);
    }
    move_type_index = 0;

    int rand_value = (rand() % total_sum_proba) + 1;  // Le nombre aléatoire doit aller de 1 à la somme totale des probabilités multiplié par 100

    int cumulative_sum = 0;
    int selected_index;

    for (int move_type_index = 0; move_type_index < DIFFERENT_MOVES_NUMBER; move_type_index++) {
        cumulative_sum += (int)(draw_table[move_type_index] * 100);
        if (rand_value <= cumulative_sum) {
            selected_index = move_type_index;
            break;
        }
    } 

    draw_table[selected_index] -= 0.01;

    return selected_index;
}


void moves_selections(int* moves_table, float* draw_table) {
    for (int move_type_index = 0; move_type_index < MOVES_TOTAL_NUMBER; move_type_index++) {
        moves_table[move_type_index] = move_draw(draw_table);
    }
}
