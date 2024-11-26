#include <stdlib.h>
#include <stdio.h>
#include "cost.h"
#include "tree.h"
#include "queue.h"
#include "moves.h"

/** 
 * @brief Trouve le chemin de mouvements pour la feuille avec le coût minimal.
 * Parcourt l'arbre avec des boucles for et met à jour le tableau best_moves.
 */
int* best_moves(t_tree* tree, int phase_movements_number) {
    int* best_moves_tab = (int*) malloc(phase_movements_number * sizeof(int));
    t_root* root_node = tree->root;
    
    int current_moves_tab[5];
    
    for (int i = 0; i < phase_movements_number; i++) {
        best_moves_tab[i] = COST_UNDEF;
    }

    int minimal_cost = COST_UNDEF;
    
    for (int i = 0; i < root_node->children_num; i++) {
        for (int j = 0; j < root_node->child_nodes[i]->children_num; j++) {
            for (int k = 0; k < root_node->child_nodes[i]->child_nodes[j]->children_num; k++) {
                for (int l = 0; l < root_node->child_nodes[i]->child_nodes[j]->child_nodes[k]->children_num; l++) {
                    for (int m = 0; m < root_node->child_nodes[i]->child_nodes[j]->child_nodes[k]->child_nodes[l]->children_num; m++) {
                        t_node* leaf_node = root_node->child_nodes[i]->child_nodes[j]->child_nodes[k]->child_nodes[l]->child_nodes[m];

                        if (leaf_node->cost != COST_UNDEF && leaf_node->cost < minimal_cost) {
                            minimal_cost = leaf_node->cost;

                            current_moves_tab[0] = root_node->child_nodes[i]->move_associated;
                            current_moves_tab[1] = root_node->child_nodes[i]->child_nodes[j]->move_associated;
                            current_moves_tab[2] = root_node->child_nodes[i]->child_nodes[j]->child_nodes[k]->move_associated;
                            current_moves_tab[3] = root_node->child_nodes[i]->child_nodes[j]->child_nodes[k]->child_nodes[l]->move_associated;
                            current_moves_tab[4] = leaf_node->move_associated;
                        }
                    }
                }
            }
        }
    }

    for (int n = 0; n < phase_movements_number; n++) {
        best_moves_tab[n] = current_moves_tab[n];
    }

    if (minimal_cost == COST_UNDEF) {
        return NULL;
    }

    return best_moves_tab;
}
