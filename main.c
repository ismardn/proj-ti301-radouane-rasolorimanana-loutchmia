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


// Fonction pour afficher les informations d'un nœud
void print_node_info(t_node* node, int level) {
    if (node == NULL) return;
    for (int i=0; i<level+1; i++) printf("  ");
    printf("Level %d - Move: %d, Cost: %d\n", level, node->move_associated, node->cost);
}

// Fonction pour parcourir l'arbre et afficher les niveaux, mouvements et coûts des nœuds
void print_tree(t_tree* tree) {
    for (int i=0; i<MOVES_TOTAL_NUMBER; i++) {
    print_tree_levels(tree->root->child_nodes[i], 1);
    printf("\n");}
}

// Fonction pour parcourir l'arbre et afficher les niveaux, mouvements et coûts des nœuds
void print_tree_levels(t_node* node, int level) {
    if (node == NULL) return;
    print_node_info(node, level);
    for (int i = 0; i < node->children_num; i++) {
        print_tree_levels(node->child_nodes[i], level + 1);    }
}

// Fonction principale
int main() {
    // Charger la carte à partir du fichier
    t_map map = createMapFromFile("maps/example1.map");

    // Initialisation des mouvements possibles
    int moves_selected[MOVES_TOTAL_NUMBER] = {0, 1, 2, 3};
    int moves_used_indexes[MOVES_NUMBER_EXECUTED] = {-1};  // Indices utilisés initialisés à -1

    // Localisation de départ
    t_localisation start_loc = {{0, 0}, NORTH};

    // Création de l'arbre
    t_tree tree;
    buildTree(&tree, moves_selected, moves_used_indexes, start_loc, map);

    // Affichage des niveaux, mouvements et coûts
    printf("Tree structure:\n");
    if (tree.root != NULL) {
        print_tree(&tree);
    } else {
        fprintf(stderr, "Error: root node is NULL\n");
    }

    // Libération de la mémoire de l'arbre (à implémenter si nécessaire)
    // Free resources in map and tree to avoid memory leaks

    return 0;
}