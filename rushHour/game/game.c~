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
  game g=malloc(sizeof(game));
  (*g).mov=0;
  (*g).nb_pieces=nb_pieces;
  for (int i=0;i<nb_pieces;i++){
    copy_piece(pieces+i,(*g).pieces[i]);
  }
  return g;
}

void delete_game (game g){
  free(g);
}

void copy_game(cgame src,game dst){
  (*dst).mov=game_nb_moves(src);
  (*dst).nb_pieces=game_nb_pieces(src);
  for (int i=0;i<game_nb_pieces(src);i++){
    copy_piece(src+i,dst+i);
  }
}

int game_nb_pieces(cgame g){
  int res=(*g).nb_pieces;
  return res;
}

cpiece game_piece(cgame g,int piece_num){
  if(piece_num<0 || piece_num>(*g).nb_pieces){
    usage("game_piece");
    exit(EXIT_FAILURE);
  }
  cpiece p;
  copy_piece((*g).piece[piece_num],p);
  return p;
}

bool game_over_hr(cgame g){
  return(get_x(game_piece(g,0))==4 && get_y(game_piece(g,0))==3);
}

int game_nb_moves(cgame g){
  return (*g).mov;
}

/*bool play_move(game g,int piece_num, dir d, int distance){
  if (distance<=0 || piece_num<0 || piece_num>(*g).game_nb_pieces(g)-1 ){
    usage("play_move");
    return false;
  }
  cpiece p;
  copy_piece(game_piece(g,piece_num),p);
  move_pieces(p,d,distance);
  for(int i=0;i<game_nb_pieces(g);i++){
    if(intersect(p,
       }
  
  
*/


