#ifndef GRAPHE
#define GRAPHE
#include "game.h"
#include "piece.h"


struct piece_s {
  int x;
  int y;
  int width;
  int height;
  bool move_x;
  bool move_y;
};

struct game_s{
  piece *pieces;
  int height;
  int width;
  int mov;
  int nb_pieces;
};

typedef struct Sommet* Sommet;
typedef struct Graphe* Graphe;

void delete_sommet(Sommet s);

void delete_graphe(Graphe g);

Sommet new_sommet(game value, int *voisins, int nbVoisins);

#endif
