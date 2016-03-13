#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "game.h"
#include "piece.h"
#include "string.h"
#define valeurCaseVide -1

piece* allouer_Tab_Piece(int nbPiece){
  piece* allouer = (piece*)malloc(nbPiece*sizeof(piece));
  return allouer;
}

void affichage(cgame g){
  printf("\n");
  printf("Nombre de mouvements effectués : %d \n",game_nb_moves(g));
  printf("\n");
  int nb = game_nb_pieces(g);
  int WIDTH = game_width(g);
  int HEIGHT = game_height(g);
  int tab_game[WIDTH][HEIGHT];
  for(int i=0; i<WIDTH; i++){
    for(int j=0; j<HEIGHT; j++) tab_game[i][j]= valeurCaseVide;
  }
  for(int i=0;i<nb;i++){
    cpiece tmp_piece = game_piece(g,i);
    int x = get_x(tmp_piece);
    int y = get_y(tmp_piece);
    for(int j=0; j<HEIGHT; j++){
      for(int k=0;k<WIDTH;k++) tab_game[x+k][y+j] = i;
    }
  }
  printf("********************\n");
  for(int yt=HEIGHT-1; yt>=0; yt--){
    printf("%d ",yt);
    for(int xt=0; xt<WIDTH; xt++){
      if(tab_game[xt][yt]==valeurCaseVide){
	printf("[ ");
      }
      else{
	printf("[%d", tab_game[xt][yt]);
      }
      printf("]");
    }
    printf("\n");
  }
  printf("  ");
  printf("*****      *****\n");
  for(int k=0;k<WIDTH-1;k++) printf(" %d ",k);
  printf("\n\n");
  printf("Pour quitter appuyez sur q \n");
  printf("\n");
}

piece* creer_Pieces_niveau_1(int *width_game,int *height_game,int* nbPieces){
  *nbPiece=10;
  *width_game=4;
  *height_game=5;
  piece* tableau1 = allouer_Tab_Piece(nbPiece);
  tableau1[0] = newpiece(1,1,2,2,true,true);
  tableau1[1] = newpiece(0,3,2,1,true,true);
  tableau1[2] = newpiece(2,3,2,1,true,true);
  tableau1[3] = newpiece(0,1,1,2,true,true);
  tableau1[4] = newpiece(1,4,2,1,true,true);
  tableau1[5] = newpiece(3,1,1,2,true,true);
  tableau1[6] = newpiece(0,0,1,1,true,true);
  tableau1[7] = newpiece(1,0,1,1,true,true);
  tableau1[8] = newpiece(2,0,1,1,true,true);
  tableau1[9] = newpiece(3,0,1,1,true,true);
  return tableau1;
}

piece* creer_Pieces_niveau_2(int *width_game,int *height_game,int* nbPieces){
  *nbPiece=10;
  *width_game=4;
  *height_game=5;
  piece* tableau2 = allouer_Tab_Piece(nbPiece);
  tableau1[0] = newpiece(1,3,2,2,true,true);
  tableau1[1] = newpiece(0,3,1,2,true,true);
  tableau1[2] = newpiece(3,3,1,2,true,true);
  tableau1[3] = newpiece(1,2,2,1,true,true);
  tableau1[4] = newpiece(0,0,1,2,true,true);
  tableau1[5] = newpiece(3,0,1,2,true,true);
  tableau1[6] = newpiece(1,0,1,1,true,true);
  tableau1[7] = newpiece(1,1,1,1,true,true);
  tableau1[8] = newpiece(2,0,1,1,true,true);
  tableau1[9] = newpiece(2,1,1,1,true,true);
  return tableau2;
}

piece* creer_Pieces_niveau_3(int *width_game,int *height_game,int* nbPieces){
  *nbPiece=10;
  *width_game=4;
  *height_game=5;
  piece* tableau3 = allouer_Tab_Piece(nbPiece);
  tableau1[0] = newpiece(1,3,2,2,true,true);
  tableau1[1] = newpiece(0,4,1,1,true,true);
  tableau1[2] = newpiece(0,3,1,1,true,true);
  tableau1[3] = newpiece(3,4,1,1,true,true);
  tableau1[4] = newpiece(3,3,1,1,true,true);
  tableau1[5] = newpiece(1,2,2,1,true,true);
  tableau1[6] = newpiece(0,0,1,2,true,true);
  tableau1[7] = newpiece(1,0,1,2,true,true);
  tableau1[8] = newpiece(2,0,1,2,true,true);
  tableau1[9] = newpiece(3,0,1,2,true,true);
  return tableau3;
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
  piece* grille = niveau_pieces(niveau,&width_game,&height_game,&nbPieces);
  game aneRouge = new_game(width_game,height_game,nbPieces,grille);
  affichage((cgame)aneRouge);
  startGame(aneRouge,nbPieces);
  return EXIT_SUCCESS;
}
