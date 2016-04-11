#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <game.h>
#include <piece.h>
#include "graph.h"

// On définit les structures

struct node{
  game game;
  int *linked;
  int nbLinked;
};


struct graph{
  node *nodes;
  int nbNodes;
};

// Fonctions sup pour Piece

bool piece_equals(cpiece P1, cpiece P2){
  bool res = true;
  res = res && get_x(P1) == get_x(P2);
  res = res && get_y(P1) == get_y(P2);
  res = res && get_height(P1) == get_height(P2);
  res = res && get_width(P1) == get_width(P2);
  res = res && is_horizontal(P1) == is_horizontal(P2);
  return res;
}

// Fonctions sup pour Game

bool game_equals_not_mov(cgame G1, cgame G2){
  bool res = true;
  res = res && game_width(G1) == game_width(G2);
  res = res && game_height(G1) == game_height(G2);
  res = res && game_nb_pieces(G1) == game_nb_pieces(G2);
  if(res){
     for(int i = 0 ; i<game_nb_pieces(G1) ; i++){
	res = res && piece_equals(game_piece(G1, i), game_piece(G2, i));
     }
  }
  return res;
}

// Fonctions sommet

node new_node(game game, int indPere){
  node newNode=malloc(sizeof(game) + sizeof(int) * 2);
  copy_game((cgame)game,newNode->game);
  newNode->linked[0] = indPere;
  newNode->nbLinked = 1;
  return newNode;
}

void delete_node(node s){
  delete_game(s->game);
  free(s->linked);
  free(s);
}

// Fonctions graph



/* void delete_graph(graph g){
  for(int i=0; i<g->nbSommets; i++){
    delete_sommet(g->sommets[i]);
  }
  free(g->sommets);
  free(g);
  } */


// Fonctions calculs
