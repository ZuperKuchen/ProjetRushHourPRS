#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <game.h>
#include "game_ar.h"
#include <piece.h>
#include "displayRH.h"
#include "displayAR.h"
#include "graph.h"
#include "displayGraph.h"
#include "solveur.h"

static void usage(char *commande){
  fprintf(stderr," %s <a|r> <filename> \n",commande);
  exit(EXIT_FAILURE);
}

int main(int argc,char* argv[]){
  if(argc!=3) usage(argv[0]);
  int width = 0;
  int height = 0;
  int nbPieces = 0;
  FILE *file = fopen(argv[2],"r");
  char* choose_game[2];
  char *rh = "r";
  char *ar = "a";
  choose_game[0] = argv[1];
  choose_game[1] = argv[2];
  if(compare(choose_game,rh)){
    config_rushHour(file,&width,&height,&nbPieces);
  }
  else if(compare(choose_game,ar)){
    config_aneRouge(file,&width,&height,&nbPieces);
  }
  else usage(argv[0]);
  return EXIT_SUCCESS;
}
