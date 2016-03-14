#ifndef _PIECE_RH_H_
#define _PIECE_RH_H_
#include <stdbool.h>


/**
 * @brief Creates a new piece.
 * @param x,y coordinates of the lower-left corner (Remark: x-axe is oriented from left to right and y-axe is oriented from bottom to top).
 * @param small indicates if the vehicle is of size 2 (small=true) or 3 (small=false)
 * @param horizontal indicates whether the vehicle can move horizontally or vertically
 * @return a pointer toward the generated piece
 */
piece new_piece_rh (int x, int y, bool small, bool horizontal);

#endif
