#ifndef UNTITLED1_DRAW_H
#define UNTITLED1_DRAW_H

/**
 * @brief Sélectionne un mouvement aléatoire basé sur un tableau de probabilités.
 * @return L'index du mouvement sélectionné.
 */
int move_draw();

/**
 * @brief Remplit un tableau de mouvements sélectionnés aléatoirement selon les probabilités du tableau.
 * @return Le tableau d'indices de mouvements sélectionnés aléatoirement.
 */
int* moves_selections();

#endif //UNTITLED1_DRAW_H
