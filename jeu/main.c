#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include "game.h"
#include "piece.h"
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
  printf("nombrePiece : %d \n",nombrePiece);
  printf("fonction creerPiece \n");
  piece* tab =(piece*)malloc(nombrePiece * sizeof(piece));
  printf("tab allouer \n");
  srand(time(NULL));
  void (*pointeurSurFonction)(bool,bool,int*,int*);
  pointeurSurFonction = casPosible;
  printf("on va rentrer dans boucle1 \n");
  for(int i=0;i<nombrePiece;i++){
    printf("i= %d\n",i);
    bool small = booleatoire();
    bool horizontal = booleatoire();
    int x;
    int y;      
    printf("on rentre dans le pointeur \n");
    (*pointeurSurFonction)(small,horizontal,&x,&y);
    printf("on sort \n");
    tab[i]=new_piece_rh(x,y,small,horizontal);
    printf("on va verifier intersect \n");
    int j=0;
    for(j=0;j<i;j++){
      printf("j= %d \n",j);
      if(i!=j){
	if(intersect((cpiece)tab[i],(cpiece)tab[j])==false){
	  continue;
	}
	else{
	  break;
	}
      }
    }
    printf("j= %d \n",j);
    if(j!=i){
      i--;
      continue;
    }
    printf("on augmente i \n");
  }
  return tab;
}

void affichage(game g){
  int nb = game_nb_pieces(g);
  for(int i=0;i<nb;i++){
    cpiece p = game_piece(g,i);
    printf(" piece %d x:%d y:%d small:%d horizontal:%d \n",i,(*p).x,(*p).y,(*p).small,(*p).horizontal);
  }
}

int main(int argc,char *argv[]){
  if(argc!=2) usage(argv[0]);
  int nbPiece = atoi(argv[1]);
  if(nbPiece<=0 || nbPiece>PieceMax) usage(argv[0]);
  piece* grille = creerPieces(nbPiece);
  game rushHour = new_game_hr(nbPiece,grille);
  affichage(rushHour);
  printf("ok");
}  
