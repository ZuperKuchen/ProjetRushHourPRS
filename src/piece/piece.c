#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "piece.h"

struct piece_s {
  int x;
  int y;
  int width;
  int height;
  bool move_x;
  bool move_y;
};

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

void delete_piece (piece p){
  free(p);
}

void copy_piece (cpiece src, piece dst){
  dst->x = get_x(src);
  dst->y = get_y(src);
  dst->width = src->width;
  dst->height = src->height;
  dst->move_x = src->move_x;
  dst->move_y = src->move_y;
}

void move_piece (piece p, dir d, int distance){
  if (can_move_x(p)){
    if(d==LEFT){
      p->x -= distance;
    }if(d==RIGHT){
      p->x += distance;
    }
  }
  if (can_move_y(p)){
    if(d==UP){
      p->y += distance;
    }if(d==DOWN){
      p->y -= distance;
    }
  }
}

bool intersect(cpiece p1, cpiece p2){
  int taille1 = get_width(p1) * get_height(p1);
  int taille2 = get_width(p2) * get_height(p2);
  int t1[taille1][2];
  int t2[taille2][2];
  int i=0;
  for(int x=0; x<get_width(p1); x++){
    for(int y=0; y<get_height(p1); y++){
      t1[i][0]=get_x(p1)+x;
      t1[i][1]=get_y(p1)+y;
      i++;
    }
  }
  i=0;
  for(int x=0; x<get_width(p2); x++){
    for(int y=0; y<get_height(p2); y++){
      t2[i][0]=get_x(p2)+x;
      t2[i][1]=get_y(p2)+y;
      i++;
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
  return p->x;
}

int get_y(cpiece p){
  return p->y;
}

int get_height(cpiece p){
  return p->height;
}

int get_width(cpiece p){
  return p->width;
}

bool is_horizontal(cpiece p){
  if(get_width(p) > get_height(p)) return true;
  return false;
}

bool can_move_x(cpiece p){
  return p->move_x;
}

bool can_move_y(cpiece p){
  return p->move_y;
}

piece new_piece (int x, int y, int width, int height, bool move_x, bool move_y){
  piece newpiece = (piece)malloc(sizeof(struct piece_s));
  newpiece->x = x;
  newpiece->y = y;
  newpiece->width = width;
  newpiece->height =height;
  newpiece->move_x = move_x;
  newpiece->move_y = move_y;
  return newpiece;
}
