#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include "moves.h"
#include "map.h"

/** 
 * @brief Vérifie si un index est déjà utilisé dans le tableau moves_used_indexes
 */
int isIndexUsed(int current_index, int* moves_used_indexes) {
    for (int i = 0; i < EXECUTED_MOVES_NUMBER - 1; i++) {
        if (current_index == moves_used_indexes[i]) return 1;
    }
    return 0;
}

/** 
 * @brief Construit l'arbre des mouvements possibles depuis la localisation actuelle
 */
void buildTree(t_tree* tree, int* moves_selected, t_localisation current_loc, t_map map) {
    int* moves_used_indexes = (int*) malloc(EXECUTED_MOVES_NUMBER * sizeof(int));

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



//Méthode facultative (ne fonctionne pas encore, à améliorer)
/*void betterPathMinLeaf(t_tree* tree, int* moves_selected, int* moves_used_indexes,t_localisation current_loc,t_map map)
{
    //Calcul des coûts de chaque case de la carte
    calculateCosts(map);
    //Initialisation d'un tableau 'chemin' avec ses indices pour mémoriser la séquence de mouvements
    int index_path = 0;
    int path[100];
    moves_used_indexes[0] = 0;
    int win = 0;
    //Initialisation du noeud racine
    tree->root = (t_root *) malloc(sizeof(t_root));
    tree->root->current_loc = current_loc;
    tree->root->children_num = SELECTED_MOVES_NUMBER;
    tree->root->child_nodes = (t_node **) malloc(tree->root->children_num * sizeof(t_node *));
    t_node *current_node = tree->root->child_nodes[0];
    //Parcours du chemin le plus prometteur
    while (current_node != NULL)
    {
        t_node *min_leaf = NULL;
        int cost_min=COST_UNDEF;
        //Cas où MARC arrive à la station de base
        if (map.costs[current_loc.pos.y][current_loc.pos.x] == 0)
        {
            printf("MARC a atteint la station de base.\n");
            win = 1;
            break;
        }
       //Cas où MARC sort de la carte
        if (isValidLocalisation(current_loc.pos, map.x_max, map.y_max) == 0)
        {
            printf("MARC est en dehors de la carte.\n");
            win=0;
            break;
        }
    }
    //Afficher le chemin suivi
    if (win)
    {
        printf("Feuille de valeur minimale trouvee avec un cout de : %d\n", current_node->cost);
        printf("Chemin suivi : \n");
        for (int i = 0; i < index_path; i++) {
            printf("%d", path[i]);
        }
    }
}*/



/** 
 * @brief Crée un nouveau noeud avec les informations spécifiées
 */
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

/** 
 * @brief Crée les noeuds enfants d'un noeud donné de manière récursive
 */
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

/**
 * @brief Affiche les informations d'un nœud spécifique avec une indentation basée sur son niveau.
 */
void display_node_info(t_node* node, int level) {
    if (node == NULL) return;

    for (int iteration = 0; iteration < level + 1; iteration++) {
        printf("  ");
    }

    printf("Level %d - Pos: %d/%d (Y/X), Ori: %s (Move: %s); Cost: %d\n", level, node->resulting_loc.pos.y, node->resulting_loc.pos.x, orientation_strings[node->resulting_loc.ori], _moves[node->move_associated], node->cost);
}

/**
 * @brief Parcourt et affiche récursivement les niveaux d'un arbre à partir d'un nœud donné.
 */
void display_tree_levels(t_node* node, int level) {
    if (node == NULL) return;

    display_node_info(node, level);

    for (int child_index = 0; child_index < node->children_num; child_index++) {
        display_tree_levels(node->child_nodes[child_index], level + 1);
    }
}

/**
 * @brief Affiche l'intégralité de l'arbre en parcourant chaque sous-arbre à partir de la racine.
 */
void display_full_tree(t_tree* tree) {
    for (int child_index=0; child_index < SELECTED_MOVES_NUMBER; child_index++) {
        display_tree_levels(tree->root->child_nodes[child_index], 1);
        
        printf("\n");
    }
}
