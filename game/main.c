#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include "game.h"
#include "piece.h"
#define PieceMax 6

static void usage(char *commande){
  fprintf(stderr," <entier> nombre de pieces < 6 \n",commande);
  exit(EXIT_FAILURE);
}

int aleatoire(int max){
    int nombre_aleatoire;
    nombre_aleatoire = rand()%max;
    return nombre_aleatoire;
}


void casPosible(bool small,bool horizontal,int *x,int *y){
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
  piece* tab[nombrePiece];
  srand(time(NULL));
  void (*pointeurSurFonction)(bool,bool,int*,int*);
  pointeurSurFonction = casPosible;
  for(int i=0;i<nombrePiece;i++){
    bool small = booleatoire();
    bool horizontal = booleatoire();
    int x;
    int y;      
    (*pointeurSurFonction)(small,horizontal,&x,&y);
    int j=0;
    for(j=0;j<i;j++){
      if(i!=j){
	if(intersect((cpiece)tab[i],(cpiece)tab[j])==false){
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
    else{
      tab[i]=new_piece_rh(x,y,small,horizontal);
    }
  }
  return tab;
}

void affichage(game g){
  int nb = game_nb_pieces(g);
  for(int i=0;i<nb;i++){
    cpiece p = game_piece(g,i);
    printf(" piece %d x:%d y:%d small:%b horizontal:%b \n",(*p).x,*p.y,*p.small,*p.horizontal;
  }
}

int main(int argc,char *argv[]){
  if(argc!=2) usage(argv[0]);
  int nbPiece = atoi(argv[1]);
  if(nbPiece<=0 || nbPiece>PieceMax) usage(argv[0]);
  piece* grille = creerPieces(nbPiece);
  game rushHour = new_game_hr(nbPiece,grille);
  affichage(rushHour);
}  
