#ifndef GRAPHE
#define GRAPHE
#include <game.h>
#include <piece.h>


typedef struct node* node;
typedef struct graph* graph;

//Fonctions outils

void copy_array(int length, int* srcArray, int* dstArray);

//Fonctions sup pour Piece

bool piece_equals(cpiece P1, cpiece P2);

//Fonctions sup pour Game

bool game_equals_not_mov(cgame G1, cgame G2);

//Fonctions sommet (node)

node new_empty_node(game game);

node new_full_node(game game, int *linked, int nbLinked);

node new_node(game game, int indPere);

void delete_node(node s);

game node_get_game(node s);

int node_get_nbLinked(node s);

int node_get_linked(node s, int ind);

void add_linked(node s, int ind);

//Fonctions graph

graph new_graph(node firstNode);

graph new_full_graph(node *tabNodes, int nbNodes);

void delete_graph(graph g);

node graph_get_node(graph g, int ind);

  int graph_get_nbNodes(graph g);

void add_node_graph(graph g, node s);

//Fonctions calculs

#endif
