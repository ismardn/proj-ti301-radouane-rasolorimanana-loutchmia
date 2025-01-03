//
// Created by flasque on 19/10/2024.
//

#ifndef UNTITLED1_MOVES_H
#define UNTITLED1_MOVES_H

#include "loc.h"
#include "map.h"

#define TYPE_OF_MOVES_NUMBER 7

#define SELECTED_MOVES_NUMBER 9
#define EXECUTED_MOVES_NUMBER 5


/**
 * @brief Array of strings for the possible moves of the robot
 */
static char _moves[TYPE_OF_MOVES_NUMBER][16] = {"FORWARD 10m", "FORWARD 20m", "FORWARD 30m", "BACK 10m", "TURN left", "TURN right", "U-turn"};

/**
 * @brief Tableau contenant les chaînes représentant les orientations cardinales.
 */
static char *orientation_strings[] = {
    "NORTH",
    "EAST",
    "SOUTH",
    "WEST"
};

/**
 * @brief Enum for the possible moves of the robot
 */
typedef enum e_move
{
    F_10, // Forward 10 m
    F_20, // Forward 20 m
    F_30, // Forward 30 m
    B_10, // Backward 10 m
    T_LEFT, // Turn left (+90°)
    T_RIGHT, // Turn right (-90°)
    U_TURN
} t_move;

/**
 * @brief function to get a t_move as a string
 * @param move : the move to convert
 * @return the string corresponding to the move
 */
char *getMoveAsString(t_move move);

/**
 * @brief function to update the localisation of the robot according to a move
 * @param loc : the localisation of the robot
 * @param move : the move to do
 * @param map : map
 * @return the new localisation of the robot
 */
t_localisation move(t_localisation, t_move, t_map);

/**
 * @brief function to update the localisation of the robot according to a move
 * @param loc : the localisation of the robot
 * @param move : the move to do
 * @param map : map
 * @return the new localisation of the robot
 */
t_localisation move(t_localisation, t_move, t_map);

/**
 * @brief function to update the localisation of the robot according to a move
 * @param loc : the localisation of the robot
 * @param move : the move to do
 * @param map : map
 * @param reg_activated : either 1 or 0 if the robot walked on a REG soil
 * @return the new localisation of the robot
 */
t_localisation move_exec(t_localisation loc, t_move move, t_map map, int* reg_activated);

/**
 * @brief wrapper function to update a single location
 * @param p_loc : the pointer to the localisation of the robot
 * @param move : the move to do
 * @param map : map
 * @return none
 */
void updateLocalisation(t_localisation *, t_move, t_map);

#endif //UNTITLED1_MOVES_H
