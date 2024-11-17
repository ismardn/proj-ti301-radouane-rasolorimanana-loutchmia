//
// Created by flasque on 19/10/2024.
//

#include "moves.h"
#include "map.h"

/* prototypes of local functions */
/* local functions are used only in this file, as helper functions */

/**
 * @brief Function to rotate the robot according to a move and its actual orientation
 * @param loc : the actual localisation of the robot
 * @param move : the move to do
 * @param map : map
 * @return the new orientation of the robot
 */
t_orientation rotate(t_localisation, t_move, t_map);

/**
 * @brief function to translate the robot according to a move and its actual position
 * @param loc : the actual localisation of the robot
 * @param move : the move to do
 * @param map : map
 * @return the new localisation of the robot
 */
t_localisation translate(t_localisation, t_move, t_map);

/* definition of local functions */

t_orientation rotate(t_localisation loc, t_move move, t_map map)
{
    int rst = 0;

    if (isValidLocalisation(loc.pos, map.x_max, map.y_max)) {
        if (map.soils[loc.pos.y][loc.pos.x] != ERG) {
            switch (move) {
                case T_LEFT:
                    rst=3;
                    break;
                case T_RIGHT:
                    rst=1;
                    break;
                case U_TURN:
                    rst=2;
                    break;
                default:
                    break;
            }
        } else {
            switch (move) {
                case T_LEFT:
                    break;
                case T_RIGHT:
                    break;
                case U_TURN:
                    rst=1;
                    break;
                default:
                    break;
            }
        }
    }

    return (loc.ori+rst)%4;
}

t_localisation translate(t_localisation loc, t_move move, t_map map)
{
    /** rules for coordinates:
     *  - x grows to the right with step of +1
     *  - y grows to the bottom with step of +1
     *  - the origin (x=0, y=0) is at the top left corner
     */

    t_position res = loc.pos;

    if (isValidLocalisation(loc.pos, map.x_max, map.y_max)) {
        if (map.soils[res.y][res.x] != ERG) {
            switch (move) {
                case F_10:
                    switch (loc.ori) {
                        case NORTH:
                            res.y = loc.pos.y - 1;
                            break;
                        case EAST:
                            res.x = loc.pos.x + 1;
                            break;
                        case SOUTH:
                            res.y = loc.pos.y + 1;
                            break;
                        case WEST:
                            res.x = loc.pos.x - 1;
                            break;
                        default:
                            break;
                    }
                    break;
                case F_20:
                    switch (loc.ori) {
                        case NORTH:
                            res.y = loc.pos.y - 2;
                            break;
                        case EAST:
                            res.x = loc.pos.x + 2;
                            break;
                        case SOUTH:
                            res.y = loc.pos.y + 2;
                            break;
                        case WEST:
                            res.x = loc.pos.x - 2;
                            break;
                        default:
                            break;
                    }
                    break;
                case F_30:
                    switch (loc.ori) {
                        case NORTH:
                            res.y = loc.pos.y - 3;
                            break;
                        case EAST:
                            res.x = loc.pos.x + 3;
                            break;
                        case SOUTH:
                            res.y = loc.pos.y + 3;
                            break;
                        case WEST:
                            res.x = loc.pos.x - 3;
                            break;
                        default:
                            break;
                    }
                    break;
                case B_10:
                    switch (loc.ori) {
                        case NORTH:
                            res.y = loc.pos.y + 1;
                            break;
                        case EAST:
                            res.x = loc.pos.x - 1;
                            break;
                        case SOUTH:
                            res.y = loc.pos.y - 1;
                            break;
                        case WEST:
                            res.x = loc.pos.x + 1;
                            break;
                        default:
                            break;
                    }
                    break;
                default:
                    break;
            }
        } else {
            switch (move) {
                case F_10:
                    break;
                case F_20:
                    switch (loc.ori) {
                        case NORTH:
                            res.y = loc.pos.y - 1;
                            break;
                        case EAST:
                            res.x = loc.pos.x + 1;
                            break;
                        case SOUTH:
                            res.y = loc.pos.y + 1;
                            break;
                        case WEST:
                            res.x = loc.pos.x - 1;
                            break;
                        default:
                            break;
                    }
                    break;
                case F_30:
                    switch (loc.ori) {
                        case NORTH:
                            res.y = loc.pos.y - 2;
                            break;
                        case EAST:
                            res.x = loc.pos.x + 2;
                            break;
                        case SOUTH:
                            res.y = loc.pos.y + 2;
                            break;
                        case WEST:
                            res.x = loc.pos.x - 2;
                            break;
                        default:
                            break;
                    }
                    break;
                case B_10:
                    break;
                default:
                    break;
            }
        }
    }

    return loc_init(res.x, res.y, loc.ori);
}

/* definitions of exported functions */

char *getMoveAsString(t_move move)
{
    return _moves[move];
}

t_localisation move(t_localisation loc, t_move move, t_map map)
{
    t_localisation new_loc;
    new_loc = translate(loc, move, map);
    new_loc.ori = rotate(loc, move, map);
    return new_loc;
}

t_localisation move_exec(t_localisation loc, t_move move, t_map map, int* reg_activated) {
    t_localisation new_loc;
    new_loc = translate(loc, move, map);
    new_loc.ori = rotate(loc, move, map);

    if (map.soils[new_loc.pos.y][new_loc.pos.x] == REG) {
        *reg_activated = 1;
    }

    return new_loc;
}

void updateLocalisation(t_localisation *p_loc, t_move m, t_map map)
{
    *p_loc = move(*p_loc, m, map);
    return;
}
