#ifndef GRAPHE
#define GRAPHE
#include <game.h>
#include <piece.h>


typedef struct node* node;
typedef struct graph* graph;


bool piece_equals(cpiece P1, cpiece P2);

bool game_equals_not_mov(cgame G1, cgame G2);

void delete_node(node s);

void delete_graph(graph g);

node new_node(game game, int indPere);

#endif
