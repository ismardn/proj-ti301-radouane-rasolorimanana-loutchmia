#include <stdlib.h>
#include "cost.h"
#include "tree.h"
#include "queue.h"
#include "moves.h"

/** 
 * @brief Trouve l'index du noeud ayant le coût le plus bas dans un tableau de noeuds.
 */
int index_lowest_cost(t_node** nodes_tab, int tab_length) {
    int minimal_cost = nodes_tab[0]->cost;
    int minimal_index = 0;
    for (int node_index = 1; node_index < tab_length; node_index++) {
        int temp_cost;
        if (nodes_tab[node_index]->cost == 0) {
            minimal_cost = nodes_tab[node_index]->cost;
            minimal_index = node_index;
            break;
        }
        if (nodes_tab[node_index]->cost < minimal_cost && nodes_tab[node_index]->cost != -1) {
            minimal_cost = nodes_tab[node_index]->cost;
            minimal_index = node_index;
        }
    }
    printf("%d|\n", minimal_index);
    return minimal_index;
}

/** 
 * @brief Génère la file des mouvements optimaux en fonction des coûts dans l'arbre.
 */
int* best_moves(t_tree* tree, int phase_movements_number) {
    int* best_moves_tab = (int*) malloc(phase_movements_number * sizeof(int));
    t_node* parent_node = tree->root;
    t_node** current_nodes_tab = parent_node->child_nodes;
    
    best_moves_tab[0] = index_lowest_cost(current_nodes_tab, parent_node->children_num);
    printf("%s\n", _moves[best_moves_tab[0]]);
    for (int nodes_tab_index = 1; nodes_tab_index < phase_movements_number; nodes_tab_index++) {
        parent_node = current_nodes_tab[best_moves_tab[nodes_tab_index - 1]];
        current_nodes_tab = parent_node->child_nodes;
        best_moves_tab[nodes_tab_index] = index_lowest_cost(current_nodes_tab, parent_node->children_num);
        printf("%s\n", _moves[best_moves_tab[nodes_tab_index]]);
    }

    return best_moves_tab;
}
