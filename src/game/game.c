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
      if (intersect(game_piece(g,piece_num),game_piece(g,i)) || is_out((piece)game_piece(g,piece_num))){
	if(d == LEFT){
	  dir_op = RIGHT;
	}if(d == RIGHT){
	  dir_op = LEFT;
	}if(d == UP){
	  dir_op = DOWN;
	}if(d == DOWN){
	  dir_op = UP;
	}
	move_piece((piece)game_piece(g,piece_num),dir_op,distance-dis);
	return false;
      }
    }
  }
  (*g).mov+=distance;
  return true;
}
       
  
/*bool play_move(game g,int piece_num, dir d, int distance){
  if (distance<=0 || piece_num<0 || piece_num>game_nb_pieces(g)-1 ){
    usage("play_move");
    return false;
  }
  int dis=distance;
  piece piece_aux=new_piece_rh(0,0,true,true);
  copy_piece(game_piece(g,piece_num),piece_aux);
  while (dis!=0){
    dis --;
    move_piece((piece)piece_aux,d,1);
    for(int i=0;i<game_nb_pieces(g);i++){
      if(i==piece_num){
	continue;
      }
      if (intersect(piece_aux,game_piece(g,i)) || is_out((piece)piece_aux)){
	delete_piece(piece_aux);
	return false;
      }
    }
  }
  copy_piece((cpiece)piece_aux,(piece)game_piece(g,piece_num));
  delete_piece(piece_aux);
  return true;
}

Ce play move est celui que l'on aurait souhaité faire, mais les données du tableau de pieces du jeu sont erronées à partir du moment où l'on réalloue la piece_aux, malgrès des heures de recherches nous ne savons toujours pas d'où vient le problème. */


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
    int w=get witdh(p_aux);
    for(int j=0; j<w; j++){
      for(int k=0; k<h; k++){
	if (x==x_aux+j && y==y_aux+k){
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
