


#include "cost.h"
#include "tree.h"
#include "queue.h"
#include "moves.h"




int index_lowest_cost(t_node* nodes_tab, int tab_length) {
    int minimal_cost = nodes_tab[0]->cost;
    int minimal_index = 0;
    for (int node_index = 1; node_index < tab_length; node_index++) {
        int temp_cost;
        if (nodes_tab[node_index]->cost < minimal_cost && nodes_tab[node_index]->cost != -1) {
            minimal_cost = nodes_tab[node_index]->cost;
            minimal_index = node_index;
        }
    }
    return minimal_index;
}


t_queue best_moves(t_tree* tree, int* best_moves_index_tab) {
    t_node* current_nodes_tab = tree->root->child_nodes;
    best_moves_index_tab[0] = index_lowest_cost(current_nodes_tab, EXECUTED_MOVES_NUMBER)
    for (int nodes_tab_index = 1; nodes_tab_index < EXECUTED_MOVES_NUMBER; nodes_tab_index++) {
        current_nodes_tab = current_nodes_tab[best_moves_index_tab[nodes_tab_index - 1]]->child_nodes;
        int tab_length = current_nodes_tab[best_moves_index_tab[nodes_tab_index - 1]]->children_num;
        best_moves_index_tab[nodes_tab_index] = index_lowest_cost(current_nodes_tab->child_nodes, previous_best_node->children_num);
    }
}

