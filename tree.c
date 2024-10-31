



#include <stdlib.h>
#include "tree.h"
#include "moves.h"





int is_index_used(int current_index, int* moves_used_indexes) {
    for (int i = 0; i < MOVES_NUMBER_EXECUTED - 1; i++) {
        if (current_index == moves_used_indexes[i]) return 1;
    }
    return 0;
}


void buildTree(t_tree* tree, int* moves_selected, int* moves_used_indexes) {
    // Créer le nœud racine avec 4 enfants pour le niveau 1
    t_node* root_node = createNode(MOVES_TOTAL_NUMBER, 0); // Le mouvement associé ici n'a pas d'importance pour la racine
    tree->root = root_node;

    // Appeler createNodes pour chaque enfant de la racine avec les mouvements correspondants
    for (int i = 0; i < MOVES_TOTAL_NUMBER; i++) {
        root_node->child_nodes[i] = createNode(MOVES_TOTAL_NUMBER - 1, moves_selected[i]); // Niveau 1 a 3 enfants
        moves_used_indexes[0] = i;  // Marque le mouvement utilisé au niveau 1
        createNodes(root_node->child_nodes[i], 1, moves_selected, moves_used_indexes);
    }
}


t_node* createNode(int children_num, int move_type_index) {
    t_node* newNode = (t_node*) malloc(sizeof(t_node));

    newNode->children_num = children_num;

    newNode->value = 0;
    newNode->move_associated = (t_move) move_type_index;

    newNode->child_nodes = (t_node**) malloc (children_num * sizeof(t_node*));
    for (int child_index = 0; child_index < children_num; child_index++) {
        newNode->child_nodes[child_index] = NULL;
    }
    return newNode;
}


void createNodes(t_node* node, int children_num_index, int* moves_selected, int* moves_used_indexes) {
    // Arrêter si nous avons atteint la profondeur maximale
    if (children_num_index == MOVES_NUMBER_EXECUTED) return;

    int i = 0;
    for (int child_index = 0; child_index < MOVES_TOTAL_NUMBER; child_index++) {
        // Vérifier que le mouvement n'est pas déjà utilisé
        if (is_index_used(child_index, moves_used_indexes)) {
            continue;
        }

        // Marquer le mouvement comme utilisé pour le niveau actuel
        moves_used_indexes[children_num_index] = child_index;

        // Créer les nœuds enfants pour le niveau 2 et 3
        if (children_num_index < MOVES_NUMBER_EXECUTED - 1) {
            node->child_nodes[i] = createNode(2, moves_selected[child_index]); // Niveau 2 a 2 enfants
        } else {
            node->child_nodes[i] = createNode(0, moves_selected[child_index]); // Niveau 3 est une feuille
        }

        // Appel récursif pour créer les sous-nœuds
        createNodes(node->child_nodes[i], children_num_index + 1, moves_selected, moves_used_indexes);

        i++;
        // Stopper quand le nombre d'enfants requis est atteint pour chaque niveau
        if (i == node->children_num) break;
    }
}
