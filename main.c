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


void print_localisation(t_localisation loc) {
    printf("Position: (%d, %d), Orientation: %d\n", loc.pos.x, loc.pos.y, loc.ori);
}

void print_node(t_node* node) {
    printf("Node at position (%d, %d), orientation %d, cost %d, move associated %d\n", 
            node->resulting_loc.pos.x, node->resulting_loc.pos.y, node->resulting_loc.ori, node->cost, node->move_associated);
}

// Fonction pour afficher les enfants d'un nœud
void print_children(t_node* node, int depth) {
    if (!node) return;

    for (int i = 0; i < depth; i++) {
        printf("  ");  // indentation pour visualiser la profondeur
    }
    print_node(node);

    for (int i = 0; i < node->children_num; i++) {
        print_children(node->child_nodes[i], depth + 1);
    }
}

int main() {
    // Charger la carte à partir du fichier
    t_map map = createMapFromFile("maps/example1.map");

    // Initialisation des mouvements possibles
    int moves_selected[MOVES_TOTAL_NUMBER] = {0, 1, 2, 3, 4, 5, 6, 7, 8};
    int moves_used_indexes[MOVES_TOTAL_NUMBER] = {-1};  // Indices utilisés initialisés à -1

    // Localisation de départ
    t_localisation start_loc = {{0, 0}, NORTH};

    // Création de l'arbre
    t_tree tree;
    buildTree(&tree, moves_selected, moves_used_indexes, start_loc, map);

    // Affichage de l'arbre
    printf("Tree structure:\n");
    print_children((t_node*)tree.root, 0);

    return 0;
}