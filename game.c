#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "game.h"
#include "piece.h"

struct game_s{
  int mov;
  int nb_pieces;
  piece pieces[];
};

void usage(char *nomfonction){
  fprintf(stderr,"An error occured in fonction %s \n",nomfonction);
}

game new_game_hr (int nb_pieces, piece *pieces){
  game g=malloc(sizeof(struct game));
  (*g).mov=0;
  (*g).nb_pieces=nb_pieces;
  for (int i=0;i<nb_pieces;i++){
    (*g).pieces[i]=*(pieces+i);
  }
  return g;
}

void delete_game (game g){
  free(g);
}

void copy_game(cgame src,game dst){
  (*dst).mov=(*src).mov;
  (*dst).nb_pieces=(*src).nb_pieces;
  for (int i=0;i<nb_pieces;i++){
    (*dst).pieces[i]=(*src).pieces[i];
  }
}

int game_nb_pieces(cgame g){
  res=(*g).nb_pieces;
  return res;
}

cpiece game_piece(cgame g,int piece_num){
  if(piece_num<0 || piece_num>(*g).nb_pieces){
    return usage("game_piece");
  }
  cpiece p=(*g).pieces[piece_num];
  return p;
}

bool game_over_hr(cgame g){
  cpiece p=game_piece(g,0);
  return ((*p).x==4 && (*p).y==3);
}




