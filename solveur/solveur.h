#ifndef SOLVEUR
#define SOLVEUR

#include "graph.h"

graph create_graph(game G, bool isRH);
int dijkstra_search(graph G);
int simple_search(graph G);

void grid_size(FILE *file,int *width,int *height);

void grid_nbPieces(FILE *file,int *nbPieces);

void create_grid(FILE *file,int nbPieces,piece *tableau);

piece* read_Config_txt(FILE *file,int *width,int *height,int *nbPieces);

bool compare(char *c1[],char *c2);

void display_solution(graph g,int number_solution,bool isRH);

void config_rushHour(FILE* file,int *width,int *height,int *nbPieces);

void config_aneRouge(FILE* file,int *width,int *height,int *nbPieces);

graph create_graph(game G, bool isRH);

int simple_search(graph G);

#endif
