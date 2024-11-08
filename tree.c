



#include <stdlib.h>
#include "tree.h"
#include "moves.h"
#include "map.h"




int isIndexUsed(int current_index, int* moves_used_indexes) {
    for (int i = 0; i < EXECUTED_MOVES_NUMBER - 1; i++) {
        if (current_index == moves_used_indexes[i]) return 1;
    }
    return 0;
}


void buildTree(t_tree* tree, int* moves_selected, int* moves_used_indexes, t_localisation current_loc, t_map map) {
    t_root* root_node = (t_root*) malloc(sizeof(t_root));

    root_node->children_num = SELECTED_MOVES_NUMBER;
    root_node->current_loc = current_loc;

    root_node->child_nodes = (t_node**) malloc(root_node->children_num * sizeof(t_node*));
    for (int child_index = 0; child_index < root_node->children_num; child_index++) {
        root_node->child_nodes[child_index] = NULL;
    }

    tree->root = root_node;

    for (int i = 0; i < SELECTED_MOVES_NUMBER; i++) {
        t_node* new_node = (t_node*) malloc(sizeof(t_node));

        new_node->parent_node = NULL;

        new_node->children_num = SELECTED_MOVES_NUMBER - 1;
        new_node->move_associated = (t_move) moves_selected[i];
        
        new_node->resulting_loc = move(current_loc, new_node->move_associated);

        if (isValidLocalisation(new_node->resulting_loc.pos, map.x_max, map.y_max)) {
            new_node->cost = map.costs[new_node->resulting_loc.pos.y][new_node->resulting_loc.pos.x];
        } else {
            new_node->cost = -1;
        }
        
        new_node->child_nodes = (t_node**) malloc(new_node->children_num * sizeof(t_node*));
        for (int child_index = 0; child_index < new_node->children_num; child_index++) {
            new_node->child_nodes[child_index] = NULL;
        }

        root_node->child_nodes[i] = new_node;
        
        moves_used_indexes[0] = i;

        createNodes(root_node->child_nodes[i], 1, moves_selected, moves_used_indexes, map);
    }
}


t_node* createNode(t_node* parent, int children_num, int move_type_index, t_map map) {
    t_node* new_node = (t_node*) malloc(sizeof(t_node));

    new_node->children_num = children_num;
    new_node->move_associated = (t_move) move_type_index;

    new_node->resulting_loc = move(parent->resulting_loc, new_node->move_associated);

    if (isValidLocalisation(new_node->resulting_loc.pos, map.x_max, map.y_max) && parent->cost != -1) {
        new_node->cost = map.costs[new_node->resulting_loc.pos.y][new_node->resulting_loc.pos.x];
    } else {
        new_node->cost = -1;
    }

    new_node->child_nodes = (t_node**) malloc(new_node->children_num * sizeof(t_node*));
    for (int child_index = 0; child_index < new_node->children_num; child_index++) {
        new_node->child_nodes[child_index] = NULL;
    }

    return new_node;
}


void createNodes(t_node* node, int children_num_index, int* moves_selected, int* moves_used_indexes, t_map map) {
    if (children_num_index == EXECUTED_MOVES_NUMBER) return;

    int i = 0;
    for (int child_index = 0; child_index < SELECTED_MOVES_NUMBER; child_index++) {
        if (isIndexUsed(child_index, moves_used_indexes)) {
            continue;
        }

        moves_used_indexes[children_num_index] = child_index;

        if (children_num_index < EXECUTED_MOVES_NUMBER - 1) {
            node->child_nodes[i] = createNode(node, SELECTED_MOVES_NUMBER - children_num_index - 1, moves_selected[child_index], map);
        } else {
            node->child_nodes[i] = createNode(node, 0, moves_selected[child_index], map);
        }

        createNodes(node->child_nodes[i], children_num_index + 1, moves_selected, moves_used_indexes, map);

        i++;

        if (i == node->children_num) break;
    }
}
