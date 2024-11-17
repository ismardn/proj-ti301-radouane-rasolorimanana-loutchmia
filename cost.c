#include <stdlib.h>
#include <stdio.h>
#include "cost.h"
#include "tree.h"
#include "queue.h"
#include "moves.h"

/** 
 * @brief Trouve l'index du noeud ayant le coût le plus bas dans un tableau de noeuds.
 */
int index_lowest_cost(t_node** nodes_tab, int tab_length) {
    int minimal_cost = _soil_cost[4];
    int minimal_index = 0;

    for (int node_index = 0; node_index < tab_length; node_index++) {
        if (nodes_tab[node_index]->cost == 0) {
            minimal_cost = nodes_tab[node_index]->cost;
            minimal_index = node_index;
            break;
        }
        if (nodes_tab[node_index]->cost < minimal_cost) {
            minimal_cost = nodes_tab[node_index]->cost;
            minimal_index = node_index;
        }
    }

    if (minimal_cost == _soil_cost[4]) {
        return -1;
    }

    return minimal_index;
}

/** 
 * @brief Génère la file des mouvements optimaux en fonction des coûts dans l'arbre.
 */
int* best_moves(t_tree* tree, int phase_movements_number) {
    int* best_moves_tab = (int*) malloc(phase_movements_number * sizeof(int));
    t_root* root_node = tree->root;
    t_node** current_nodes_tab = root_node->child_nodes;
    int index_lowest_cost_value = index_lowest_cost(current_nodes_tab, root_node->children_num);;
    
    if (best_moves_tab[0] == -1) {
        return NULL;
    }
    best_moves_tab[0] = current_nodes_tab[index_lowest_cost_value]->move_associated;

    for (int nodes_tab_index = 1; nodes_tab_index < phase_movements_number; nodes_tab_index++) {
        t_node* parent_node = current_nodes_tab[index_lowest_cost_value];
        current_nodes_tab = parent_node->child_nodes;

        int index_lowest_cost_value = index_lowest_cost(current_nodes_tab, parent_node->children_num);
        if (index_lowest_cost_value == -1) {
            return NULL;
        }

        best_moves_tab[nodes_tab_index] = current_nodes_tab[index_lowest_cost_value]->move_associated;
    }

    return best_moves_tab;
}
