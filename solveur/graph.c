#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <game.h>
#include <piece.h>
#include "graph.h"

// On définit les structures

struct node{
  game game;
  int nbLinked;
  int linked[];
};

struct graph{
  int nbNodes;
  node nodes[];
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
    int pieces = 0;
    for(int i = 0 ; i<game_nb_pieces(G1) ; i++){
      for(int j = 0 ; j<game_nb_pieces(G2) ;j++){
	if(piece_equals(game_piece(G1, i), game_piece(G2, j))){
	  pieces ++;
	  break;
	}
      }
      if(i+1 != pieces) return false;
    }
    if(pieces == game_nb_pieces(G1)) return true;
  }
  return false;
}

game copy_game_for_solver(cgame src){
  int nb_pieces = game_nb_pieces(src);
  int w = game_width(src);
  int h = game_height(src);
  piece tab[nb_pieces];
  for (int i=0;i<nb_pieces;i++){
    tab[i] = copy_piece_for_solver(game_piece(src, i));
  }
  game dst = new_game (w, h, nb_pieces, tab);
  return dst;
}


// Fonctions sommet

node new_empty_node(game game){
  node newNode=malloc(sizeof(game) + sizeof(int));
  newNode->game = copy_game_for_solver((cgame)game);
  newNode->nbLinked = 0;
  return newNode;
}

node new_full_node(game game, int *linked, int nbLinked){
  node newNode=malloc(sizeof(game) + sizeof(int) + sizeof(int) * nbLinked);
  newNode->game = copy_game_for_solver((cgame)game);
  newNode->nbLinked = nbLinked;
  for(int i=0; i<nbLinked; i++){
    newNode->linked[i] = linked[i];
  }
  return newNode;
}

node new_node(game game, int indPere){
  node newNode=malloc(sizeof(game) + sizeof(int) * 2);
  newNode->game = copy_game_for_solver((cgame)game);
  newNode->linked[0] = indPere;
  newNode->nbLinked = 1;
  return newNode;
}

void delete_node(node s){
  delete_game(s->game);
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


node add_linked(node s, int ind){
  for(int i=0; i<node_get_nbLinked(s); i++){
    if(node_get_linked(s, i) == ind){
      return s;
    }
  }
  int newSize = node_get_nbLinked(s)+1;
  node d = realloc(s,sizeof(game) + sizeof(int) + sizeof(int) * newSize);
  d->linked[newSize-1] = ind;
  d->nbLinked = newSize;
  return d;
}

node copy_node(node s){
  node d = new_full_node(s->game, s->linked, s->nbLinked);
  return d;
}


// Fonctions graph

graph new_graph(node firstNode){
  graph newGraph = malloc(sizeof(int) + sizeof(node));
  newGraph->nbNodes = 1;
  newGraph->nodes[0] = copy_node(firstNode);
  return newGraph;
}

graph new_full_graph(node *tabNodes, int nbNodes){
  graph newGraph = malloc(sizeof(int) + sizeof(node)*nbNodes);
  newGraph->nbNodes = nbNodes;
  for(int i=0; i<nbNodes; i++){
    newGraph->nodes[i] = copy_node(tabNodes[i]);
  }
  return newGraph;
}

void delete_graph(graph g){
  for(int i=0; i<g->nbNodes; i++){
    delete_node(g->nodes[i]);
  }
  free(g);
}

node graph_get_node(graph g, int ind){
  return g->nodes[ind];
}

int graph_get_nbNodes(graph g){
  return g->nbNodes;
}

graph add_node_graph(graph g, node s){
  int newSize = graph_get_nbNodes(g)+1;
  graph d = realloc(g, sizeof(int) + sizeof(node) * newSize);
  d->nodes[newSize-1] = copy_node(s);
  d->nbNodes = newSize;
  return d;
}

void put_new_adress(graph g, node new, int ind){
  g->nodes[ind] = new;
}

// Fonctions calculs

game *different_cases(game gameUse, int *nbCases){
  *nbCases = 0;
  int nbPieces = game_nb_pieces((cgame)gameUse);
  game tmpGame;
  game *tabGame = calloc(sizeof(game), nbPieces*4);
  for(int i = 0; i<nbPieces; i++){
    piece tmpPiece = (piece)game_piece((cgame) gameUse, i);
    if(can_move_x((cpiece)tmpPiece)){
      tmpGame = copy_game_for_solver((cgame) gameUse);
      if(play_move(tmpGame, i, LEFT, 1)){
	  tabGame[*nbCases] = copy_game_for_solver((cgame) tmpGame);
	  (*nbCases)++;
      }
      delete_game(tmpGame);
      tmpGame = copy_game_for_solver((cgame) gameUse);
      if(play_move(tmpGame, i, RIGHT, 1)){
	  tabGame[*nbCases] = copy_game_for_solver((cgame) tmpGame);
	  (*nbCases)++;
      }
      delete_game(tmpGame);
    }
    if(can_move_y((cpiece)tmpPiece)){
      tmpGame = copy_game_for_solver((cgame) gameUse);
      if(play_move(tmpGame, i, UP, 1)){
	  tabGame[*nbCases] = copy_game_for_solver((cgame) tmpGame);
	  (*nbCases)++;
      }
      delete_game(tmpGame);
      tmpGame = copy_game_for_solver((cgame) gameUse);
      if(play_move(tmpGame, i, DOWN, 1)){
	  tabGame[*nbCases] = copy_game_for_solver((cgame) tmpGame);
	  (*nbCases)++;
      }
      delete_game(tmpGame);
    }
  }
  return tabGame;
}

int already_exists(game gameUse, graph graph){
  node n;
  game g;
  for(int i = 0 ; i < graph_get_nbNodes(graph) ; i++){
    n = graph_get_node(graph, i);
    g = node_get_game(n);
    if(game_equals_not_mov(g, gameUse)){
      return i;
    }
  }
  return -1;
}

void free_cases(game *cases, int nbCases){
  for(int i = 0; i<nbCases; i++){
    delete_game(cases[i]);
  }
  free(cases);
}

