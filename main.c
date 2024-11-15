#include <stdio.h>
#include "map.h"
#include "moves.h"
#include "tree.h"
#include "loc.h"



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
static char **orientation_strings[] = {
    "NORTH",
    "EAST",
    "SOUTH",
    "WEST"
};


// Fonction pour afficher les informations d'un nœud
void print_node_info(t_node* node, int level) {
    if (node == NULL) return;
    for (int i=0; i<level+1; i++) printf("  ");
    printf("Level %d - Pos: %d/%d (Y/X), Ori:%s (Move: %s); Cout:%d\n", level, node->resulting_loc.pos.y, node->resulting_loc.pos.x, orientation_strings[node->resulting_loc.ori], _moves[node->move_associated], node->cost);
}

// Fonction pour parcourir l'arbre et afficher les niveaux, mouvements et coûts des nœuds
void print_tree_levels(t_node* node, int level) {
    if (node == NULL) return;
    print_node_info(node, level);
    for (int i = 0; i < node->children_num; i++) {
        print_tree_levels(node->child_nodes[i], level + 1);    }
}

// Fonction pour parcourir l'arbre et afficher les niveaux, mouvements et coûts des nœuds
void print_tree(t_tree* tree) {
    for (int i=0; i<SELECTED_MOVES_NUMBER; i++) {
    print_tree_levels(tree->root->child_nodes[i], 1);
    printf("\n");}
}


// Fonction principale
int main() {
    // Charger la carte à partir du fichier
    t_map map = createMapFromFile("maps/example1.map");
    
    printf("\n\n\n");

    // Initialisation des mouvements possibles
    int moves_selected[SELECTED_MOVES_NUMBER] = {0, 1, 2, 3, 4, 5, 6, 7, 8};
    int moves_used_indexes[EXECUTED_MOVES_NUMBER] = {-1};  // Indices utilisés initialisés à -1

    // Localisation de départ
    t_localisation start_loc;
    start_loc.pos.y = 5;
    start_loc.pos.x = 4;
    start_loc.ori = NORTH;
    
    // Création de l'arbre
    t_tree tree;
    //betterPathMinLeaf(&tree, moves_selected, moves_used_indexes, start_loc, map);
    buildTree(&tree, moves_selected, moves_used_indexes, start_loc, map);

    // Affichage des niveaux, mouvements et coûts
    if (tree.root != NULL) {
        print_tree(&tree);
    }

    // Libération de la mémoire de l'arbre (à implémenter si nécessaire)

    return 0;
}