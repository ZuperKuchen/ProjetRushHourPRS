#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "piece.h"


struct piece_s {
  int x;
  int y;
  bool small;
  bool horizontal;
};

piece new_piece_rh (int x, int y, bool small, bool horizontal){
  piece newpiece = malloc(sizeof(struct piece_s));
  (*newpiece).x = x;
  (*newpiece).y = y;
  (*newpiece).small = small;
  (*newpiece).horizontal = horizontal;
  return newpiece;
}

void delete_piece (piece p){
  free(p);
}

void copy_piece (cpiece src, piece dst){
  (*dst).x = (*src).x;
  (*dst).y = (*src).y;
  (*dst).small = (*src).small;
  (*dst).horizontal = (*src).horizontal;
}

void move_piece (piece p, dir d, int distance){
  if ((*p).horizontal==true){
    if(d==LEFT){
      (*p).x -= distance;
    }if(d==RIGHT){
      (*p).x += distance;
    }
  }if ((*p).horizontal==false){
    
    

