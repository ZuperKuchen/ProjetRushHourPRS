#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include "game.h"
#include "piece.h"
#include "string.h"
#define PieceMax 6

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
    if((get_y(tab[i])==3) && is_horizontal(tab[i])){
      i--;
      continue;
    }
    int j=0;  
    for(j=0;j<i;j++){
      if(i!=j){
	if((intersect((cpiece)tab[i],(cpiece)tab[j])==false)){
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


void lancerJeu(game g,int nbPiece){
  while(!game_over_hr(g)){
    int num,distance;
    printf("numéro de la piece à bouger ?\n");
    for(int a=0;a<nbPiece;a++) printf(" %d ",a);
    printf("\n");
    scanf("%d",&num);
    if(is_horizontal(game_piece(g,num)))printf(" quelle direction? LEFT ? RIGHT?");
    else printf("quelle direction? UP,DOWN?\n");
    char direction[20];
    fgets(direction, sizeof(direction), stdin);
    printf("direction: %s.\n", direction);
    if(go!=LEFT && go!=RIGHT && go!=UP && go!=DOWN){
      printf("choisissez parmis les propositions..");
      continue;
    }
    printf("la distance?");
    scanf("%d",&distance);
    play_move(g,num,go,distance);
    affichage(g);
   }
  printf("Bravo ! le jeu est terminé");
}


int main(int argc,char *argv[]){
  if(argc!=2) usage(argv[0]);
  int nbPiece = atoi(argv[1]);
  if(nbPiece<=0 || nbPiece>PieceMax) usage(argv[0]);
  piece* grille = creerPieces(nbPiece);
  game rushHour = new_game_hr(nbPiece,grille);
  affichage(rushHour);
  lancerJeu(rushHour,nbPiece);
}  
