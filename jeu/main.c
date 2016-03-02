#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include "game.h"
#include "piece.h"
#include "string.h"
#define PieceMax 7
#define small_size 2
#define big_size 3

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
    if(get_height(p1)*get_width(p1)==big_size && get_height(p2)*get_width(p2)==big_size){
      if(is_horizontal(p1)==true && is_horizontal(p2)==true){
	return false;
      }
    }
  }
  else if(get_x(p1)==get_x(p2)){
    if(is_horizontal(p1)==false && is_horizontal(p2)==false){
      if(get_height(p1)*get_width(p1)==big_size || get_height(p2)*get_width(p2)==big_size){
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
    if((get_y(tab[i])==big_size) && is_horizontal(tab[i])){
      i--;
      continue;
    }
    int j=0;  
    for(j=0;j<i;j++){
      if(i!=j){
	if((intersect((cpiece)tab[i],(cpiece)tab[j])==false)){
	  continue;
	}
	else if (!testCreerPiece(tab[i],tab[j])){
	  break;
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
  int nb = game_nb_pieces(g);
  int tab_game[6][6];
  for(int i=0; i<6; i++){
    for(int j=0; j<6; j++){
      tab_game[i][j]= 15;
    }
  }
  for(int i=0;i<nb;i++){
    cpiece temp_piece = game_piece(g,i);
    int x = get_x(temp_piece);
    int y = get_y(temp_piece);
    if(is_horizontal(temp_piece)){
      for(int j=0; j<get_width(temp_piece); j++){
	tab_game[x+j][y] = i;
      }
    }else{
      for(int j=0; j<get_height(temp_piece); j++){
	tab_game[x][y+j] = i;
      }
    }
  }
  for(int yt=5; yt>=0; yt--){
    for(int xt=0; xt<6; xt++){
      if(tab_game[xt][yt]==15){
	printf("[ ]");
      }
      else{
	printf("[%d]", tab_game[xt][yt]);
      }
    }
    printf("\n");
  }
}

void startGame(game g,int nbPiece){
  while(!game_over_hr(g)){
    int num,distance,d;
    dir direction;
    printf("numéro de la piece à bouger ?\n");
    for(int a=0;a<nbPiece;a++) printf(" %d",a);
    printf("\n");
    scanf("%d",&num);

    if(is_horizontal(game_piece(g,num))){
      printf(" quelle direction? l/r ?\n");
      fscanf(stdin,"%d",&d);
      //printf("direction: %c\n", d);
    }
    else {
      printf("quelle direction? u/d ?\n");
      fscanf(stdin,"%d",&d);
      //printf("direction: %c\n", d);
    }
    bool test=true;
    switch(d){
    case 'l':
      printf("LEFT\n");
      direction=LEFT;
      break;
    case 'r':
      printf("RIGHT\n");
      direction=RIGHT;
      break;
    case 'u':
      printf("UP\n");
      direction=UP; 
      break;
    case 'd':
      printf("DOWN\n");
      direction=DOWN;
      break;
    default:
      printf("choisissez parmis les propositions..\n");
      test=false;
      break;
    }
    if (!test) continue;
    printf("la distance?\n");
    scanf("%d",&distance);
    bool goodMove=play_move(g,num,direction,distance);
    if (goodMove==false) {
      printf("deplacement impossible \n");
      continue;
    }
    affichage(g);
   }
  printf("Bravo ! le jeu est terminé");
}



int main(int argc,char *argv[]){
  if(argc!=2) usage(argv[0]);
  int nbPiece = atoi(argv[1])+1;
  if(nbPiece<=0 || nbPiece>PieceMax) usage(argv[0]);
  piece* grille = creerPieces(nbPiece);
  game rushHour = new_game_hr(nbPiece,grille);
  affichage(rushHour);
  startGame(rushHour,nbPiece);
}  
