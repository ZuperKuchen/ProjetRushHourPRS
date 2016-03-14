#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "game.h"
#include "piece.h"
#include "string.h"
#define WIDTH 4
#define HEIGHT 5
#define VALEUR_CASE_VIDE -1

piece* allouer_Tab_Piece(int nbPiece){
  piece* allouer = (piece*)malloc(nbPiece*sizeof(piece));
  return allouer;
}

void affichage(cgame g){
  printf("\n");
  printf("Nombre de mouvements effectués : %d \n",game_nb_moves(g));
  printf("\n");
  int nb = game_nb_pieces(g);
  int tab_game[WIDTH][HEIGHT];
  for(int i=0; i<WIDTH; i++){
    for(int j=0; j<HEIGHT; j++) tab_game[i][j]= VALEUR_CASE_VIDE;
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
      if(tab_game[xt][yt]==VALEUR_CASE_VIDE){
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

piece* creer_Pieces_niveau_1(int* nbPieces){
  *nbPiece=10;
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

piece* creer_Pieces_niveau_2(int* nbPieces){
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

piece* creer_Pieces_niveau_3(int* nbPieces){
  *nbPiece=10;
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

bool string_to_dir(dir *d,char *dir_str){
  res=true;
  if (strcmp(dir_str,"left\n")==0){
    *d=LEFT;
  }
  else if (strcmp(dir_str,"right\n")==0){
    *d=RIGHT;
  }
  else if (strcmp(dir_str,"up\n")==0){
    *d=UP;
  }
  else if (strcmp(dir_str,"down\n")==0){
    *d=DOWN;
  }
  else {
    res=false;
  }
}

bool wantToQuit(char *dir_str){
  if (strcmp(dir_str,"q\n")==0){
    return true;
  }
  return false;
}

void startGame(game g,int nbPiece){
  while(!game_over_ar(g)){
    char num_str[3],distance[3],dir_str[7];
    dir direction;
    printf("Numéro de la piece à bouger ?\n");
    for(int a=0;a<nbPiece;a++) printf(" %d",a);
    printf("\n");
    fgets(num_str,3,stdin);
    int num=atoi(num_str);
    if(num<0 || num>=nbPiece){
      printf("Choisissez parmis les propositions..\n");
      continue;
    }
    if (wantToQuit(num_str)==true){
      exit(EXIT_SUCCESS);
    }
    printf("Quelle direction? left/right/up/down?\n");
    fgets(dir_str,7,stdin);
    if (wantToQuit(dir_str)==true){
      exit(EXIT_SUCCESS);
    }
    bool test = true;
    if (string_to_dir(&direction,dir_str)==false)
      printf("Choisissez parmis les propositions..\n");
    test = false;
    }
    if (!test) continue;
    printf("La distance?\n");
    fgets(distance,3,stdin);
    if (wantToQuit(distance)==true){
      exit(EXIT_SUCCESS);
    }
    bool goodMove=play_move(g,num,direction,atoi(distance));
    if (goodMove==false) {
      printf("Deplacement impossible \n");
      continue;
    }
    printf("___________________________________________ \n");
    affichage(g);
   }
  printf("Bravo ! le jeu est terminé\n ");
  printf("___________________________________________ \n");
}


piece* niveau_pieces(int niveau,int* nbPieces){
  switch(niveau){
  case 1:
    piece* tab=creer_Pieces_niveau_1(&nbPieces);
    break;
  case 2:
    piece* tab=creer_Pieces_niveau_2(&nbPieces);
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
  int niveau,nbPieces;
  printf("choisissez parmis les 3 niveaux \n niveau 1 tapez 1 \n niveau 2 tapez 2 \n niveau 3 tapez 3\n");
  scanf("%d",&niveau);
  while(niveau!=1 && niveau !=2 && niveau!=3){
    printf("choisissez parmis les niveaux proposés !\n");
    scanf("%d",&niveau);
  }
  piece* grille = niveau_pieces(niveau,&nbPieces);
  game aneRouge = new_game(WIDTH,HEIGHT,nbPieces,grille);
  affichage((cgame)aneRouge);
  startGame(aneRouge,nbPieces);
  printf("Voulez vous rejouez? oui/non \n");
  fgets(rejouer,6,stdin);
  while(strcmp(rejouer,"oui\n")==0){
    printf("choisissez parmis les 3 niveaux \n niveau 1 tapez 1 \n niveau 2 tapez 2 \n niveau 3 tapez 3\n");
    scanf("%d",&niveau);
    while(niveau!=1 && niveau !=2 && niveau!=3){
      printf("choisissez parmis les niveaux proposés !\n");
      scanf("%d",&niveau);
    }
    piece* grille = niveau_pieces(niveau,&nbPieces);
    game anneRouge = new_game(WIDTH,HEIGHT,nbPieces,grille);
    affichage((cgame)anneRouge);
    startGame(rushHour,nbPieces);
    printf("Voulez vous rejouez? oui/non \n");
    fgets(rejouer,6,stdin);
  }
  return EXIT_SUCCESS;
}
