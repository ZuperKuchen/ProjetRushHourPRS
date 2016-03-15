#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "game.h"
#include "piece.h"
#include "game_ar"

bool game_over_ar(cgame g){
  return (get_x(game_piece(g,0))==1 &&  get_y(game_piece(g,0))==0);
}
