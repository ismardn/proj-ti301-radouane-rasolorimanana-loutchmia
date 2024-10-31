



#ifndef UNTITLED1_TREE_H
#define UNTITLED1_TREE_H

#include "moves.h"


typedef struct s_node
{
    struct s_node** child_nodes;
    int value;
    int children_num;
    t_move move_associated;
} t_node;


typedef struct s_tree
{
    t_node* root;
} t_tree;


int is_index_used(int current_index, int* moves_used_indexes);


void buildTree(t_tree* tree, int* moves_selected, int* moves_used_indexes);


t_node* createNode(int children_num, int move_type_index);


void createNodes(t_node* node, int children_num_index, int* moves_selected, int* moves_used_indexes);


#endif //UNTITLED1_TREE_H
