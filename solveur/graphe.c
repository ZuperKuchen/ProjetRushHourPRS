#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include "piece.h"
#include "graphe.h"

struct Sommet{
  game value;
  int *voisins;
  int nbVoisins;
};

struct Graphe{
  Sommet *sommets;
  int nbSommets;
};

void delete_sommet(Sommet s){
  delete_game(s->value);
  free(s->voisins);
  free(s);
}

void delete_graphe(Graphe g){
  for(int i=0; i<g->nbSommets; i++){
    delete_sommet(g->sommets[i]);
  }
  free(g->sommets);
  free(g);
}

Sommet new_sommet(game value, int *voisins, int nbVoisins){
  Sommet newSommet=malloc(value->nb_pieces * sizeof(piece) + sizeof(int)*4+(nbVoisins+1)*sizeof(int));
  copy_game((cgame)value,newSommet->value);
  for(int i=0; i<nbVoisins; i++){
    newSommet->voisins[i]=voisins[i];
  }
  newSommet->nbVoisins=nbVoisins;
  return newSommet;
}
  
/*Graphe new_graphe(Sommet sommets, int nbSommets){
  Graphe newGraphe = malloc(nbSommets * (value->nb_pieces * sizeof(piece) + sizeof(int)*4+(nbVoisins+1)*sizeof(int))+sizeof(int));
  for(int i=0; i<nbSommets; ++i){
  newGraphe->sommets[i] = newSommet(*/
