#ifndef UNTITLED1_DRAW_H
#define UNTITLED1_DRAW_H

/**
 * @brief Sélectionne un mouvement aléatoire basé sur un tableau de probabilités.
 * @param draw_table Tableau de probabilités pour chaque type de mouvement.
 *                   Chaque élément représente la probabilité d'un mouvement spécifique.
 * @return L'index du mouvement sélectionné.
 */
int move_draw(float* draw_table);

/**
 * @brief Remplit un tableau de mouvements sélectionnés aléatoirement selon les probabilités du tableau.
 * @param moves_table Tableau dans lequel les mouvements sélectionnés seront stockés.
 *                    Chaque élément correspond à un mouvement choisi.
 * @param draw_table Tableau de probabilités utilisé pour influencer la sélection de chaque mouvement.
 */
void moves_selections(int* moves_table, float* draw_table);

#endif //UNTITLED1_DRAW_H
