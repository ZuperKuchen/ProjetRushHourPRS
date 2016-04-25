#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "rushHour.h"
#include "piece.h"
#include "game.h"

static void usage(char *commande){
  fprintf(stderr," %s <entier> nombre de pieces <=9 \n",commande);
  exit(EXIT_FAILURE);
}

int main(int argc,char *argv[]){
  bool replay=true;
  if(argc!=2) usage(argv[0]);
  int nbPieces = atoi(argv[1]);
  if(nbPieces<=0 || nbPieces>PIECE_MAX) usage(argv[0]);
  play_replay(replay,nbPieces);
  return EXIT_SUCCESS;
}  
