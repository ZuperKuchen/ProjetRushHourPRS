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

// Fonctions outils

void copy_array(int length, int* srcArray, int* dstArray){
  for(int i = 0 ; i < length ; i++){
    dstArray[i] = srcArray[i];
  }
}

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

piece copy_piece_for_solver(cpiece src){
  int x = get_x(src);
  int y = get_y(src);
  int width = get_width(src);
  int height = get_height(src);
  bool move_x = can_move_x(src);
  bool move_y = can_move_y(src);
  piece dst = new_piece (x, y, width, height, move_x, move_y);
  return dst;
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

game copy_game_for_solver(cgame src){
  int nb_pieces = game_nb_pieces(src);
  int w = game_width(src);
  int h = game_height(src);
  piece tab[nb_pieces];
  for (int i=0;i<game_nb_pieces(src);i++){
    tab[i] = copy_piece_for_solver(game_piece(src, i));
  }
  game dst = new_game (w, h, nb_pieces, tab);
  return dst;
}

// Fonctions sommet

node new_empty_node(game game){
  node newNode=malloc(sizeof(game) + sizeof(int));
  copy_game((cgame)game,newNode->game);
  newNode->nbLinked = 0;
  return newNode;
}

node new_full_node(game game, int *linked, int nbLinked){
  node newNode=malloc(sizeof(game) + sizeof(int) * nbLinked + sizeof(int));
  copy_game((cgame)game,newNode->game);
  int nodelinked[nbLinked];
  newNode->linked = nodelinked;
  copy_array(nbLinked, linked, newNode->linked);
  newNode->nbLinked = nbLinked;
  return newNode;
}

node new_node(game game, int indPere){
  node newNode=malloc(sizeof(game) + sizeof(int) * 2);
  copy_game((cgame)game,newNode->game);
  int linked[0];
  newNode->linked = linked;
  newNode->linked[0] = indPere;
  newNode->nbLinked = 1;
  return newNode;
}

void delete_node(node s){
  delete_game(s->game);
  free(s->linked);
  free(s);
}

game node_get_game(node s){
  return s->game;
}

int node_get_nbLinked(node s){
  return s->nbLinked;
}

int node_get_linked(node s, int ind){
  return s->linked[ind];
}

void add_linked(node s, int ind){
  game g = s->game;
  int newSize = s->nbLinked + 1;
  int newTab[newSize];
  for(int i = 0; i<newSize-1 ; i++){
    newTab[i] = s->linked[i];
  }
  newTab[newSize-1] = ind;
  delete_node(s);
  s = new_full_node(g, newTab, newSize);
}

node copy_node(node src){
  
}


// Fonctions graph

graph new_graph(node firstNode){
  graph newGraph = malloc(sizeof(node) + sizeof(int));
  newGraph->nodes = malloc(sizeof(node));
  newGraph->nodes[0] = firstNode;
  newGraph->nbNodes = 1;
  return newGraph;
}

graph new_full_graph(node *tabNodes, int nbNodes){
  graph newGraph = malloc(sizeof(node)*nbNodes + sizeof(int));
  newGraph->nodes = tabNodes;
  newGraph->nbNodes = nbNodes;
  return newGraph;
}
  

void delete_graph(graph g){
  for(int i=0; i<g->nbNodes; i++){
    delete_node(g->nodes[i]);
  }
  free(g->nodes);
  free(g);
}

node graph_get_node(graph g, int ind){
  return g->nodes[ind];
}

int graph_get_nbNodes(graph g){
  return g->nbNodes;
}

void add_node_graph(graph g, node s){
  int newSize = g->nbNodes + 1;
  node *newTab = malloc(sizeof(node)*newSize);
  for(int i = 0; i<newSize-1 ; i++){
    newTab[i] = g->nodes[i];
  }
  newTab[newSize-1] = s;
  delete_graph(g);
  g = new_full_graph(newTab, newSize);
}

// Fonctions calculs
