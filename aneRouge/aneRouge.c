#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "game.h"
#include "piece.h"
#include "string.h"

piece* allouer_Tab_Piece(int nbPiece){
  piece* allouer = (piece*)malloc(nbPiece*sizeof(piece));
  return allouer;
}

piece* creer_Pieces_niveau_1(int *width_game,int *height_game,int* nbPieces){
  *nbPiece=10;
  *width_game=4;
  *height_game=5;
  piece* tableau1 = allouer_Tab_Piece(nbPiece);
  tableau1[0] = newpiece(1,4,2,1,true,false);
  tableau1[1] = newpiece(0,3,2,1,false,false);
  tableau1[2] = newpiece(2,3,2,1,false,false);
  tableau1[3] = newpiece(0,1,1,2,false,false);
  tableau1[4] = newpiece(1,1,2,2,false,false);
  tableau1[5] = newpiece(3,1,1,2,false,false);
  tableau1[6] = newpiece(0,0,1,1,false false);
  tableau1[7] = newpiece(1,0,1,1,false false);
  tableau1[8] = newpiece(2,0,1,1,false false);
  tableau1[9] = newpiece(3,0,1,1,false false);
  return tableau1;
}


piece* niveau_pieces(int niveau,int *width_game,int *height_game,int* nbPieces){
  switch(niveau){
  case 1:
    piece* tab=creer_Pieces_niveau_1(&width_game,&height_game,&nbPieces);
    break;
  case 2:
    piece* tab=creer_Pieces_niveau_2(&width_game,&height_game,&nbPieces);
    break;
  case 3:
    piece* tab=creer_Pieces_niveau_3(&width_game,&height_game,&nbPieces);
    break;
  default:
    printf("erreur de niveau \n");
  }
  return tab;
}

int main(int argc,char* argv[]){
  char rejouer[6];
  int niveau,width_game,height_game,nbPieces;
  printf("choisissez parmis les 3 niveaux \n niveau 1 tapez 1 \n niveau 2 tapez 2 \n niveau 3 tapez 3\n");
  scanf("%d",&niveau);
  while(niveau!=1 && niveau !=2 && niveau!=3){
    printf("choisissez parmis les niveaux proposés !\n");
    scanf("%d",&niveau);
  }
  int width_game,height_game;
  piece* grille = niveau_pieces(int niveau,&width_game,&height_game,&nbPieces);
  game aneRouge = new_game(width_game,height_game,nbPieces,grille);
  affichage((cgame)aneRouge);
  startGame(aneRouge,nbPieces);
  return EXIT_SUCCESS;
}
