#ifndef UNTITLED1_COST_H
#define UNTITLED1_COST_H

#include "tree.h"
#include "queue.h"
#include "moves.h"

/**
 * @brief Trouve l'index du noeud ayant le coût le plus bas dans un tableau de noeuds.
 * @param nodes_tab Tableau de pointeurs vers des noeuds.
 * @param tab_length Longueur du tableau de noeuds.
 * @return Index du noeud avec le coût minimal dans le tableau.
 */
int index_lowest_cost(t_node* nodes_tab, int tab_length);

/**
 * @brief Génère la file des mouvements optimaux en fonction des coûts dans l'arbre.
 * @param tree Pointeur vers l'arbre de mouvements.
 * @param best_moves_index_tab Tableau des index correspondant aux meilleurs mouvements.
 * @return File (t_queue) contenant les mouvements optimaux.
 */
t_queue best_moves(t_tree* tree, int* best_moves_index_tab);

#endif // UNTITLED1_COST_H
