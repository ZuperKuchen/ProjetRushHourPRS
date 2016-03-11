#ifndef _GAME_RH_H_
#define _GAME_RH_H_
#include <stdbool.h>
#include "piece.h"
#include "game.h"

/**
 * @brief Create a new game given a starting position defined by a set of pieces.
 * The pieces of the created game are copies of the ones given as argument.
 * The number of moves of the game is set to 0.
 * @param nb_pieces number of pieces g
 * @param pieces array of pieces. The pieces given here are not modified by this function.
 * @return a pointer toward the generated game
 */

game new_game_hr (int nb_pieces, piece *pieces);


/**
 * @brief Test is the game is over (i.e. if the piece 0 has reached the exit).
 * @return true if the piece number 0 has coordinates (4,3)
*/

bool game_over_hr(cgame g);



#enfif
