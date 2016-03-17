#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "game.h"
#include "piece.h"
#define TAILLE 6

struct game_s{
  int height;
  int width;
  int mov;
  int nb_pieces;
  piece pieces[];
};



void usage(char *nomfonction){
  fprintf(stderr,"An error occured in fonction %s \n",nomfonction);
}

game new_game_hr (int nb_pieces, piece *pieces){
  game g=new_game (6, 6,nb_pieces, pieces);
}

bool game_over_hr(cgame g){
  return(get_x(game_piece(g,0))==4 && get_y(game_piece(g,0))==3);
}


void delete_game (game g){
  free(g);
}

void copy_game(cgame src,game dst){
  dst->mov=game_nb_moves(src);
  dst->nb_pieces=game_nb_pieces(src);
  for (int i=0;i<game_nb_pieces(src);i++){
    copy_piece((cpiece)src->pieces[i],dst->pieces[i]);
  }
}

int game_nb_pieces(cgame g){
  return g->nb_pieces;
}

cpiece game_piece(cgame g,int piece_num){
  if(piece_num<0 || piece_num>=(*g).nb_pieces){
    usage("game_piece");
    exit(EXIT_FAILURE);
  }
  return (cpiece)g->pieces[piece_num];
}

int game_nb_moves(cgame g){
  return g->mov;
}

bool is_out(piece p){
  return (get_x(p)>(TAILLE-get_width(p)) || get_y(p)>(TAILLE-get_height(p))|| get_x(p)<0 || get_y(p)<0); 
}


void reverse_direction(dir d,dir* dir_op){
  if(d == LEFT){
    *dir_op = RIGHT;
  }if(d == RIGHT){
    *dir_op = LEFT;
  }if(d == UP){
    *dir_op = DOWN;
  }if(d == DOWN){
    *dir_op = UP;
  }
}

bool is_not_valid_move(game g,int piece_num,int i){
  return (intersect(game_piece(g,piece_num),game_piece(g,i)) || is_out((piece)game_piece(g,piece_num)));
}

bool play_move(game g,int piece_num, dir d, int distance){
  if (distance<=0 || piece_num<0 || piece_num>game_nb_pieces(g)-1 ){
    usage("play_move");
    return false;
  }
  int dis=distance;
  dir dir_op;
  while (dis!=0){
    dis --;
    move_piece((piece)game_piece(g,piece_num),d,1);
    for(int i=0;i<game_nb_pieces(g);i++){
      if(i==piece_num){
	continue;
      }
      if (is_not_valid_move(g,piece_num,i)){
	reverse_direction(d,&dir_op);
	move_piece((piece)game_piece(g,piece_num),dir_op,distance-dis);
	return false;
      }
    }
  }
  (*g).mov+=distance;
  return true;
}


//////////// version 2////////////
 
game new_game (int width, int height, int nb_pieces, piece *pieces){
  game g=(game)malloc(sizeof(game));
  g->mov=0;
  g->nb_pieces=nb_pieces;
  g->height=height;
  g->width=width;
  for(int i=0; i<nb_pieces; i++){
    g->pieces[i]=pieces[i];
  }
  return g;
}


int game_width(cgame g){
  return g->width;
}


int game_height(cgame g){
  return g->height;
}

///V1 game_square_piece //// On compare chaque "carré" de chaque piece avec le carré test
int game_square_piece (game g, int x, int y){
  for (int i=0;i<game_nb_pieces(g);i++){
    cpiece p_aux= game_piece(g,i);
    int x_p= get_x(p_aux);
    int y_p=get_y(p_aux);
    int h=get_height(p_aux);
    int w=get_width(p_aux);
    for(int j=0; j<w; j++){
      for(int k=0; k<h; k++){
	if (x==x_p+j && y==y_p+k){
	  return i;
	}
      }
    }
  }
  return -1;
}

///v2 game_square_piece//// On crée une piece carré de coté 1 en (x,y) et on test succesivement si il y a intersection avec les pieces du jeu

/*
int game_square_piece (game g, int x, int y){
  piece p_test=new_piece (x, y,1,1,false,false);
  for(int i=0;i<game_nb_pieces(g);i++){
    cpiece p_aux= game_piece(g,i);
    if (intersect(p_aux,(cpiece)p_test)){
      return i;
      delete_piece(p_test);
    }
  }
  return -1;
  delete_piece(p_test);
}

*/
