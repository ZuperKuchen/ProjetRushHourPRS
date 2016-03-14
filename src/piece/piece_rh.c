#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "piece.h"

piece new_piece_rh (int x, int y, bool small, bool horizontal){
  int width,height;
  bool move_x,move_y;
  piece newpiece = (piece)malloc(sizeof(struct piece_s));
  if(horizontal){
    move_x = true;
    move_y = false;
    if(small){
      width = 2;
      height = 1;
    }else{
      width = 3;
      height = 1;
    }
  }else{
    move_x = false;
    move_y = true;
    if(small){
      width = 1;
      height = 2;
    }
    else{
      width = 1;
      height = 3;
    }
  }
  newpiece = new_piece(x,y,width,height,move_x,move_y);
  return newpiece;
}
