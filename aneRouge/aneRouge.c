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

piece* malloc_tab_piece(int nbPiece){                                 //permet d'alouer un tableau de struct piece
  piece* allouer = (piece*)malloc(nbPiece*sizeof(piece));
  return allouer;
}

void cases_display(cgame g,int nb,int tab_game[WIDTH][HEIGHT]){      //on affiche les valeur
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

void init_display(cgame g,int nb,int tab_game[WIDTH][HEIGHT]){       //on initialise les cases 
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

void display(cgame g){
  printf("\n");
  printf("Nombre de mouvements effectués : %d \n",game_nb_moves(g));
  printf("\n");
  int nb = game_nb_pieces(g);
  int tab_game[WIDTH][HEIGHT];
  init_display(g,nb,tab_game);
  printf("  ************\n");
  cases_display(g,nb,tab_game);
  printf("Pour quitter appuyez sur q \n");
  printf("\n");
}

piece* create_pieces_level_1(int* nbPieces){             //niveau 1
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

piece* create_pieces_level_2(int* nbPieces){            //niveau 2
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

bool string_to_dir(dir *d,char *dir_str){           //on donne la direction
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

bool want_to_quit(char *dir_str){                //pour quitter quand le joueur le souhaite
  if (strcmp(dir_str,"q\n")==0){
    return true;
  }
  return false;
}

int choose_number_piece(int nbPiece, game g){           //on choisis la piece à bouger
  char num_str[3];
  bool good_num = false;
  int num;
  while(!good_num){
    good_num = true;
    printf("Numéro de la pièce à bouger ?\n");
    for(int a=0;a<nbPiece;a++) printf(" %d",a);
    printf("\n");
    fgets(num_str,3,stdin);
    if (want_to_quit(num_str)==true){
      delete_game(g);
      exit(EXIT_SUCCESS);
    }
    num=atoi(num_str);
    if(num<0 || num>=nbPiece){
      printf("Choisissez parmis les propositions :\n");
      good_num = false;
    }
  }
  return num;
}

bool choose_direction(game g,int num_piece,dir *direction){    //on choisis la direction
  char dir_str[7];
  bool vert;
  printf("Quelle direction ? left/right/up/down ?\n");
  fgets(dir_str,7,stdin);
  if (want_to_quit(dir_str)==true){
    delete_game(g);
    exit(EXIT_SUCCESS);
  }
  if (string_to_dir(direction,dir_str)==false){
    printf("Choisissez parmis les propositions..\n");
    return false;
  }
  return true;
}

int choose_distance(game g){       //on choisis la distance
  char distance[3];
  printf("La distance ?\n");
  fgets(distance,3,stdin);
  if (want_to_quit(distance)==true){
    delete_game(g);
    exit(EXIT_SUCCESS);
  }
  int dist = atoi(distance);
  return dist;
}

void start_game(game g,int nbPiece){
  while(!game_over_ar(g)){
    dir direction;
    int num = choose_number_piece(nbPiece, g);
    bool test = choose_direction(g,num,&direction);
    if (!test) continue;
    int distance = choose_distance(g);
    bool goodMove=play_move(g,num,direction,distance);
    if (goodMove==false) {
      printf("Deplacement impossible \n");
      continue;
    }
    printf("___________________________________________ \n");
    display(g);
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
    printf("Choisissez parmis les 3 niveaux : \n Niveau 1 tapez 1 \n Niveau 2 tapez 2 \n Niveau 3 tapez 3\n");
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
  display((cgame)aneRouge);
  start_game(aneRouge,*nbPieces);
  printf("Voulez vous rejouez? oui/non \n");
  delete_game(aneRouge);
  fgets(rejouer,6,stdin);
  if(strcmp(rejouer,"oui\n")==0)return true;
  else return false;
}

void play_replay(bool replay,int *nbPieces){
  while(replay==true){
    int niveau = choose_level();
    replay=play(niveau,nbPieces);
  }
}

int main(int argc,char* argv[]){
  int nbPieces;
  bool replay = true;
  play_replay(replay,&nbPieces);
  return EXIT_SUCCESS;
}
