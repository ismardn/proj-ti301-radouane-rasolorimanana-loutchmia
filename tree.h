#ifndef UNTITLED1_TREE_H
#define UNTITLED1_TREE_H

#include "moves.h"
#include "map.h"

/** 
 * @brief Structure représentant un noeud dans l'arbre de mouvements
 */
typedef struct s_node
{
    struct s_node* parent_node; /**< Pointeur vers le noeud parent */
    struct s_node** child_nodes; /**< Tableau de pointeurs vers les noeuds enfants */
    int children_num; /**< Nombre d'enfants associés au noeud */

    t_move move_associated; /**< Mouvement associé à ce noeud */
    t_localisation resulting_loc; /**< Localisation résultant de ce mouvement */

    int cost; /**< Coût du noeud, basé sur la carte */
} t_node;

/** 
 * @brief Structure représentant la racine de l'arbre
 */
typedef struct s_root
{
    struct s_node** child_nodes; /**< Tableau de pointeurs vers les noeuds enfants */
    int children_num; /**< Nombre d'enfants de la racine */

    t_localisation current_loc; /**< Localisation actuelle de la racine */
} t_root;

/** 
 * @brief Structure représentant l'arbre de mouvements complet
 */
typedef struct s_tree
{
    t_root* root; /**< Pointeur vers la racine de l'arbre */
} t_tree;

/** 
 * @brief Vérifie si un index a déjà été utilisé
 * @param current_index L'index actuel
 * @param moves_used_indexes Tableau des index déjà utilisés
 * @param children_num_index Indice correspondant au "niveau" de l'arbre
 * @return 1 si l'index est utilisé, 0 sinon
 */
int isIndexUsed(int current_index, int* moves_used_indexes, int children_num_index);

/** 
 * @brief Construit l'arbre des mouvements possibles à partir de la localisation actuelle
 * @param tree Pointeur vers l'arbre
 * @param moves_selected Mouvements sélectionnés pour construire l'arbre
 * @param current_loc Localisation actuelle
 * @param map Carte actuelle contenant les coûts
 */
void buildTree(t_tree* tree, int* moves_selected, t_localisation current_loc, t_map map);

/** 
 * @brief Calcule le chemin optimal dans l'arbre (fonction expérimentale, à améliorer)
 */
void betterPathMinLeaf(t_tree* tree, int* moves_selected, int* moves_used_indexes, t_localisation current_loc, t_map map);

/** 
 * @brief Crée un nouveau noeud dans l'arbre
 * @param parent Noeud parent du nouveau noeud
 * @param children_num Nombre d'enfants pour ce noeud
 * @param move_type_index Type de mouvement pour ce noeud
 * @param map Carte actuelle avec les coûts
 * @return Pointeur vers le nouveau noeud
 */
t_node* createNode(t_node* parent, int children_num, int move_type_index, t_map map);

/** 
 * @brief Crée les noeuds enfants pour un noeud donné
 * @param node Noeud pour lequel on crée des enfants
 * @param children_num_index Index du nombre d'enfants
 * @param moves_selected Mouvements sélectionnés
 * @param moves_used_indexes Index des mouvements déjà utilisés
 * @param map Carte actuelle avec les coûts
 */
void createNodes(t_node* node, int children_num_index, int* moves_selected, int* moves_used_indexes, t_map map);

/**
 * @brief Affiche les informations d'un nœud spécifique avec une indentation basée sur son niveau.
 * @param node Pointeur vers le nœud dont les informations doivent être affichées.
 * @param level Niveau du nœud dans l'arbre, utilisé pour structurer l'affichage.
 */
void display_node_info(t_node* node, int level);

/**
 * @brief Parcourt et affiche récursivement les niveaux d'un arbre à partir d'un noeud donné.
 * @param node Pointeur vers le nœud de départ pour l'affichage.
 * @param level Niveau actuel dans l'arbre pour structurer l'affichage.
 */
void display_tree_levels(t_node* node, int level) ;

/**
 * @brief Affiche l'intégralité de l'arbre en parcourant chaque sous-arbre à partir de la racine.
 * @param tree Pointeur vers l'arbre à afficher.
 */
void display_full_tree(t_tree* tree);




#endif //UNTITLED1_TREE_H
