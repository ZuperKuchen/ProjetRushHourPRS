#ifndef GRAPHE
#define GRAPHE
#include <game.h>
#include <piece.h>

typedef struct node* node;
typedef struct graph* graph;

//Fonctions sup pour Piece

bool piece_equals(cpiece P1, cpiece P2);
piece copy_piece_for_solver(cpiece src);  //Renvoie une nouvelle piece qui
                                          //prend les meme valeurs que src
//Fonctions sup pour Game

bool game_equals_not_mov(cgame G1, cgame G2);
game copy_game_for_solver(cgame src);     //Comme le copy_piece_for_solveur

//Fonctions sommet (node)

node new_empty_node(game game);

node new_full_node(game game, int *linked, int nbLinked);

node new_node(game game, int indPere);

void delete_node(node s);

game node_get_game(node s);

int node_get_nbLinked(node s);

int node_get_linked(node s, int ind);

node add_linked(node s, int ind);

node copy_node(node src);

void delete_node(node s);

//Fonctions graph

graph new_graph(node firstNode);

graph new_full_graph(node *tabNodes, int nbNodes);

void delete_graph(graph g);

node graph_get_node(graph g, int ind);

int graph_get_nbNodes(graph g);

graph add_node_graph(graph g, node s);

void put_new_adress(graph g, node new, int ind);

void delete_graph(graph g);

//Fonctions calculs

game *different_cases(game gameUse, int* nbCases); //A partir d'un GAME, renvoie
                                                   //un tableau des GAME possibles
                                                   //après un mouv.

int already_exists(game game, graph graph);        //Vérifie si le game existe deja
                                                   //dans le graph

void free_cases(game *cases, int nbCases);         //free le tableau de game 
                                                   //retourné par different_cases

#endif
