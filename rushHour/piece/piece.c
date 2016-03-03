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
  if (is_horizontal(p)){
    if(d==LEFT){
      (*p).x -= distance;
    }if(d==RIGHT){
      (*p).x += distance;
    }
  }if (!is_horizontal(p)){
    if(d==UP){
      (*p).y += distance;
    }if(d==DOWN){
      (*p).y -= distance;
    }
  }
}

bool intersect(cpiece p1, cpiece p2){
  int taille1 = get_width(p1) * get_height(p1);
  int taille2 = get_width(p2) * get_height(p2);
  int t1[3][2];
  int t2[3][2];
  if(is_horizontal(p1)){
    for(int i=0 ; i<taille1 ; i++){
      t1[i][0]=(*p1).x + i;
      t1[i][1]=(*p1).y;
    }
  }else{
    for(int i=0 ; i<taille1 ; i++){
      t1[i][0]=(*p1).x;
      t1[i][1]=(*p1).y + i;
    }
  }
  if(is_horizontal(p2)){
    for(int i=0 ; i<taille2 ; i++){
      t2[i][0]=(*p2).x + i;
      t2[i][1]=(*p2).y;
    }
  }else{
    for(int i=0 ; i<taille2 ; i++){
      t2[i][0]=(*p2).x;
      t2[i][1]=(*p2).y + i;
    }
  }
  for(int i=0; i<taille1; i++){
    for(int j=0; j<taille2; j++){
      if(t1[i][0] == t2[j][0] && t1[i][1] == t2[j][1]){
	return true;
      }
    }
  }
  return false;
}

int get_x(cpiece p){
  return (*p).x;
}

int get_y(cpiece p){
  return (*p).y;
}

int get_height(cpiece p){
  if(!is_horizontal(p)){
    if (is_small(p)){
      return 2;
    }else{
      return 3;
    }
  }else{
    return 1;
  }
}

int get_width(cpiece p){
  if(is_horizontal(p)){
    if (is_small(p)){
      return 2;
    }else{
      return 3;
    }
  }else{
    return 1;
  }
}

bool is_horizontal(cpiece p){
  return (*p).horizontal;
}


bool is_small(cpiece p){
  return (*p).small;
}
