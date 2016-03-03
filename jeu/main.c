#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include "game.h"
#include "piece.h"
#include "string.h"
#define PIECE_MAX 6
#define SMALL_SIZE 2
#define BIG_SIZE 3
#define GAME_SIZE 6

static void usage(char *commande){
  fprintf(stderr," %s <entier> nombre de pieces <=6 \n",commande);
  exit(EXIT_FAILURE);
}

int aleatoire(int max){
    int nombre_aleatoire;
    nombre_aleatoire = rand()%max;
    return nombre_aleatoire;
}


void casPossible(bool small,bool horizontal,int *x,int *y){
  if(horizontal){
    if(small){
      *x=aleatoire(5);
    }
    else{
      *x=aleatoire(4);
    }
    *y=aleatoire(6);
  }
  else{
    if(small){
      *y=aleatoire(5);
    }
    else{
      *y=aleatoire(4);
    }
    *x=aleatoire(6);
  }
}


bool booleatoire(void){
  int nombre_aleatoire = rand()%10;
  if(nombre_aleatoire<5) return true;
  else return false;
}


bool testCreerPiece(piece p1,piece p2){
  if(get_y(p1)==get_y(p2)){
    if(get_height(p1)*get_width(p1)==BIG_SIZE && get_height(p2)*get_width(p2)==BIG_SIZE){
      if(is_horizontal(p1)==true && is_horizontal(p2)==true){
	return false;
      }
    }
  }
  else if(get_x(p1)==get_x(p2)){
    if(is_horizontal(p1)==false && is_horizontal(p2)==false){
      if(get_height(p1)*get_width(p1)==BIG_SIZE || get_height(p2)*get_width(p2)==BIG_SIZE){
	return false;
      }
    }
  }
  return true;
}

piece* creerPieces(int nombrePiece){
  piece* tab =(piece*)malloc(nombrePiece * sizeof(piece));
  srand(time(NULL));
  tab[0]=new_piece_rh(0,3,true,true);
  for(int i=1;i<nombrePiece;i++){
    bool small = booleatoire();
    bool horizontal = booleatoire();
    int x;
    int y;      
    casPossible(small,horizontal,&x,&y);
    tab[i]=new_piece_rh(x,y,small,horizontal);
    if((get_y(tab[i])==BIG_SIZE) && is_horizontal(tab[i])){
      i--;
      continue;
    }
    int j=0;  
    for(j=0;j<i;j++){
      if(i!=j){
	if (!testCreerPiece(tab[i],tab[j])) break;
	else if((intersect((cpiece)tab[i],(cpiece)tab[j])==false)){
	  continue;
	}
	else{
	  break;
	}
      }
    }
    if(j!=i){
      i--;
      continue;
    }
  }
  return tab;
}

void affichage(game g){
  printf("\n");
  printf("Nombre de mouvements effectués : %d \n",game_nb_moves(g));
  int nb = game_nb_pieces(g);
  int tab_game[GAME_SIZE][GAME_SIZE];
  for(int i=0; i<GAME_SIZE; i++){
    for(int j=0; j<GAME_SIZE; j++){
      tab_game[i][j]= 15;
    }
  }
  for(int i=0;i<nb;i++){
    cpiece tmp_piece = game_piece(g,i);
    int x = get_x(tmp_piece);
    int y = get_y(tmp_piece);
    if(is_horizontal(tmp_piece)){
      for(int j=0; j<get_width(tmp_piece); j++){
	tab_game[x+j][y] = i;
      }
    }else{
      for(int j=0; j<get_height(tmp_piece); j++){
	tab_game[x][y+j] = i;
      }
    }
  }
  for(int yt=GAME_SIZE-1; yt>=0; yt--){
    for(int xt=0; xt<GAME_SIZE; xt++){
      if(tab_game[xt][yt]==15){
	printf("[ ");
      }
      else{
	printf("[%d", tab_game[xt][yt]);
      }
      if(xt==5 && yt==3){
	printf("{");
      }else{
	printf("]");
      }
    }
    printf("\n");
  }
  printf("Pour quitter appuyez sur q \n");
  printf("\n");
}

void startGame(game g,int nbPiece){
  while(!game_over_hr(g)){
    char num[3],distance[3],dir_str[7];
    dir direction;
    bool vert;
    printf("Numéro de la piece à bouger ?\n");
    for(int a=0;a<nbPiece;a++) printf(" %d",a);
    printf("\n");
    fgets(num,3,stdin);
    if(is_horizontal(game_piece(g,atoi(num)))){
      printf("Quelle direction? left/right ?\n");
      vert=false;
    }
    else {
      printf("Quelle direction? up/down ?\n");
      vert=true;
    }
    fgets(dir_str,7,stdin);
    bool test=true;
    if (strcmp(dir_str,"left\n")==0 && !vert){
      direction=LEFT;
    }
    else if (strcmp(dir_str,"right\n")==0 && !vert){
      direction=RIGHT;
    }
    else if (strcmp(dir_str,"up\n")==0 && vert){
      direction=UP;
    }
    else if (strcmp(dir_str,"down\n")==0 && vert){
      direction=DOWN;
    }
    else {
      printf("Choisissez parmis les propositions..\n");
      test=false;
    }
    if (!test) continue;
    printf("La distance?\n");
    fgets(distance,3,stdin);
    bool goodMove=play_move(g,atoi(num),direction,atoi(distance));
    if (goodMove==false) {
      printf("Deplacement impossible \n");
      continue;
    }
    affichage(g);
   }
  printf("Bravo ! le jeu est terminé");
}



int main(int argc,char *argv[]){
  if(argc!=2) usage(argv[0]);
  int nbPiece = atoi(argv[1]);
  if(nbPiece<=0 || nbPiece>PIECE_MAX) usage(argv[0]);
  piece* grille = creerPieces(nbPiece);
  game rushHour = new_game_hr(nbPiece,grille);
  affichage(rushHour);
  startGame(rushHour,nbPiece);
}  
