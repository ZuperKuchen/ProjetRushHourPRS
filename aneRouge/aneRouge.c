#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "game.h"
#include "game_ar.h"
#include "piece.h"
#include "string.h"
#define WIDTH 4
#define HEIGHT 5
#define VALEUR_CASE_VIDE -1

piece* malloc_tab_piece(int nbPiece){
  piece* allouer = (piece*)malloc(nbPiece*sizeof(piece));
  return allouer;
}

void remplissage_affichage(cgame g,int nb,int tab_game[WIDTH][HEIGHT]){
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
  printf("***      ***\n");
  printf(" ");
  for(int k=0;k<WIDTH;k++) printf("  %d",k);
  printf("\n\n");
}

void initialisation_affichage(cgame g,int nb,int tab_game[WIDTH][HEIGHT]){
  for(int i=0; i<WIDTH; i++){
    for(int j=0; j<HEIGHT; j++) tab_game[i][j]= VALEUR_CASE_VIDE;
  }
  for(int i=0;i<nb;i++){
    cpiece tmp_piece = game_piece(g,i);
    int x = get_x(tmp_piece);
    int y = get_y(tmp_piece);
    for(int j=0; j<get_height(tmp_piece); j++){
      for(int k=0;k<get_width(tmp_piece);k++) tab_game[x+k][y+j] = i;
    }
  }
}

void affichage(cgame g){
  printf("\n");
  printf("Nombre de mouvements effectués : %d \n",game_nb_moves(g));
  printf("\n");
  int nb = game_nb_pieces(g);
  int tab_game[WIDTH][HEIGHT];
  initialisation_affichage(g,nb,tab_game);
  printf("  ************\n");
  remplissage_affichage(g,nb,tab_game);
  printf("Pour quitter appuyez sur q \n");
  printf("\n");
}

piece* create_pieces_level_1(int* nbPieces){
  *nbPieces=10;
  piece* tableau1 = malloc_tab_piece(*nbPieces);
  tableau1[0] = new_piece(1,1,2,2,true,true);
  tableau1[1] = new_piece(0,3,2,1,true,true);
  tableau1[2] = new_piece(2,3,2,1,true,true);
  tableau1[3] = new_piece(0,1,1,2,true,true);
  tableau1[4] = new_piece(1,4,2,1,true,true);
  tableau1[5] = new_piece(3,1,1,2,true,true);
  tableau1[6] = new_piece(0,0,1,1,true,true);
  tableau1[7] = new_piece(1,0,1,1,true,true);
  tableau1[8] = new_piece(2,0,1,1,true,true);
  tableau1[9] = new_piece(3,0,1,1,true,true);
  return tableau1;
}

piece* create_pieces_level_2(int* nbPieces){
  *nbPieces=10;
  piece* tableau2 = malloc_tab_piece(*nbPieces);
  tableau2[0] = new_piece(1,3,2,2,true,true);
  tableau2[1] = new_piece(0,3,1,2,true,true);
  tableau2[2] = new_piece(3,3,1,2,true,true);
  tableau2[3] = new_piece(1,2,2,1,true,true);
  tableau2[4] = new_piece(0,0,1,2,true,true);
  tableau2[5] = new_piece(3,0,1,2,true,true);
  tableau2[6] = new_piece(1,0,1,1,true,true);
  tableau2[7] = new_piece(1,1,1,1,true,true);
  tableau2[8] = new_piece(2,0,1,1,true,true);
  tableau2[9] = new_piece(2,1,1,1,true,true);
  return tableau2;
}

piece* create_pieces_level_3(int* nbPieces){
  *nbPieces=10;
  piece* tableau3 = malloc_tab_piece(*nbPieces);
  tableau3[0] = new_piece(1,3,2,2,true,true);
  tableau3[1] = new_piece(0,4,1,1,true,true);
  tableau3[2] = new_piece(0,3,1,1,true,true);
  tableau3[3] = new_piece(3,4,1,1,true,true);
  tableau3[4] = new_piece(3,3,1,1,true,true);
  tableau3[5] = new_piece(1,2,2,1,true,true);
  tableau3[6] = new_piece(0,0,1,2,true,true);
  tableau3[7] = new_piece(1,0,1,2,true,true);
  tableau3[8] = new_piece(2,0,1,2,true,true);
  tableau3[9] = new_piece(3,0,1,2,true,true);
  return tableau3;
}

bool string_to_dir(dir *d,char *dir_str){
  bool res=true;
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
  return res;
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
    if (string_to_dir(&direction,dir_str)==false){
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


piece* level_pieces(int niveau,int* nbPieces){
  piece* tab;
  switch(niveau){
  case 1:
    tab=create_pieces_level_1(nbPieces);
    break;
  case 2:
    tab=create_pieces_level_2(nbPieces);
    break;
  case 3:
    tab=create_pieces_level_3(nbPieces);
    break;
  default:
    printf("erreur de niveau \n");
  }
  return tab;
}

int choose_level(){
  bool level = false;
  char str_niveau[4];
  int niveau;
  while(level==false){
    level = true;
    printf("choisissez parmis les 3 niveaux \n niveau 1 tapez 1 \n niveau 2 tapez 2 \n niveau 3 tapez 3\n");
    fgets(str_niveau,3,stdin);
    niveau = atoi(str_niveau);
    if(niveau!=1 && niveau !=2 && niveau!=3){
      printf("choisissez parmis les niveaux proposés !\n");
      level == false;
    }
  }
  return niveau;
}

bool play(int niveau,int *nbPieces){
  char rejouer[6];
  piece* grille = level_pieces(niveau,nbPieces);
  game aneRouge = new_game(WIDTH,HEIGHT,*nbPieces,grille);
  affichage((cgame)aneRouge);
  startGame(aneRouge,*nbPieces);
  printf("Voulez vous rejouez? oui/non \n");
  fgets(rejouer,6,stdin);
  if(strcmp(rejouer,"oui\n")==0)return true;
  else return false;
}

void play_Replay(bool replay,int *nbPieces){
  while(replay==true){
    int niveau = choose_level();
    replay=play(niveau,nbPieces);
  }
}

int main(int argc,char* argv[]){
  int nbPieces;
  bool replay = true;
  play_Replay(replay,&nbPieces);
  return EXIT_SUCCESS;
}
