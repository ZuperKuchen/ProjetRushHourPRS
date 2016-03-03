#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "game.h"
#include "piece.h"
#define TAILLE 6

struct game_s{
  int mov;
  int nb_pieces;
  piece pieces[];
};

void usage(char *nomfonction){
  fprintf(stderr,"An error occured in fonction %s \n",nomfonction);
}


game new_game_hr (int nb_pieces, piece *pieces){
  game g=(game)malloc(sizeof(game));
  (*g).mov=0;
  (*g).nb_pieces=nb_pieces;
  for(int i=0; i<nb_pieces; i++){
    (*g).pieces[i]=pieces[i];
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
    cpiece piece_aux = (*src).pieces[i];
    copy_piece(piece_aux,(*dst).pieces[i]);
  }
}

int game_nb_pieces(cgame g){
  return (*g).nb_pieces;
}

cpiece game_piece(cgame g,int piece_num){
  if(piece_num<0 || piece_num>=(*g).nb_pieces){
    usage("game_piece");
    exit(EXIT_FAILURE);
  }
  return (cpiece)(*g).pieces[piece_num];
}

bool game_over_hr(cgame g){
  return(get_x(game_piece(g,0))==4 && get_y(game_piece(g,0))==3);
}

int game_nb_moves(cgame g){
  return (*g).mov;
}

bool is_out(piece p){
  return (get_x(p)>(TAILLE-get_width(p)) || get_y(p)>(TAILLE-get_height(p))); 
}
  

bool play_move(game g,int piece_num, dir d, int distance){
  if (distance<=0 || piece_num<0 || piece_num>game_nb_pieces(g)-1 ){
    usage("play_move");
    return false;
  }
  cpiece piece_aux=game_piece(g,piece_num);
  while (distance!=0){
    distance --;
    move_piece((piece)piece_aux,d,1);
    for(int i=0;i<game_nb_pieces(g);i++){
      if(i==piece_num){
	continue;
      }
      if (intersect(piece_aux,game_piece(g,i)) || is_out((piece)piece_aux)){
	return false;
      }
    }
  }
  copy_piece(piece_aux,(piece)game_piece(g,piece_num));
  (*g).mov+=1;
  return true;
}
       
  
  



