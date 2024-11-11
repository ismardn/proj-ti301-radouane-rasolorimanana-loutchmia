



#ifndef UNTITLED1_TREE_H
#define UNTITLED1_TREE_H

#include "moves.h"
#include "map.h"



typedef struct s_node
{   
    struct s_node* parent_node;

    struct s_node** child_nodes;
    int children_num;

    t_move move_associated;
    t_localisation resulting_loc;

    int cost;
} t_node;


typedef struct s_root
{
    struct s_node** child_nodes;
    int children_num;

    t_localisation current_loc;
} t_root;


typedef struct s_tree
{
    t_root* root;
} t_tree;


int isIndexUsed(int current_index, int* moves_used_indexes);


void buildTree(t_tree* tree, int* moves_selected, int* moves_used_indexes, t_localisation current_loc, t_map map);

void betterPathMinLeaf(t_tree* tree, int* moves_selected, int* moves_used_indexes, t_localisation current_loc,t_map map);

t_node* createNode(t_node* parent, int children_num, int move_type_index, t_map map);


void createNodes(t_node* node, int children_num_index, int* moves_selected, int* moves_used_indexes, t_map map);


#endif //UNTITLED1_TREE_H
