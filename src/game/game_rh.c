#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "game.h"
#include "piece.h"
#include "game_rh.h"


game new_game_hr (int nb_pieces, piece *pieces){
  game g=new_game (6, 6,nb_pieces, *pieces);
}

bool game_over_hr(cgame g){
  return(get_x(game_piece(g,0))==4 && get_y(game_piece(g,0))==3);
}
