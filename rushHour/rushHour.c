#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include "game.h"
#include "piece.h"
#include "string.h"
#define PIECE_MAX 9
#define SMALL_SIZE 2
#define BIG_SIZE 3
#define GAME_SIZE 6

static void usage(char *commande){
  fprintf(stderr," %s <entier> nombre de pieces <=9 \n",commande);
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
      *x=aleatoire(5);                               /* en fonction de si la piece est small/big et horizontal/vertical*/
    }                                                /* on génère aléatoirement des valeur x et y en fonction des cas  possible */
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


bool booleatoire(void){                                /* booleatoire génère un nombre aleatoire entre 0 et 9 compris,soit 10 nombres*/ 
  int nombre_aleatoire = rand()%10;                    /* si le nombre est 0,1,2,3 ou 4, booleatoire renvoie true, false sinon*/
  if(nombre_aleatoire<5) return true;
  else return false;
}


bool testCreerPiece(piece p1,piece p2){               /* testCreerPiece regarde quelques cas particulier impossible a résoudre*/
  if(get_y(p1)==get_y(p2)){                           /* pour le joueur */
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
    tab[i]=new_piece_rh(x,y,small,horizontal);                /* on creer la piece i et on la met dans le tableaux de pieces */
    if((get_y(tab[i])==3) && is_horizontal(tab[i])){          /* on verifie qu'elle n'est pas horizontal avec y=3 */
      i--;
      continue;                                               /* si erreur on re-crée la piece */
    }
    int j=0;  
    for(j=0;j<i;j++){
      if (!testCreerPiece(tab[i],tab[j])) break;
      else if((intersect((cpiece)tab[i],(cpiece)tab[j])==false)){
	continue;
      }
      else{
	break;
      }
    }
    if(j!=i){                                                /* de meme ici si intersection */
      i--;
      continue;
    }
  }
  return tab;
}

void affichage(cgame g){
  printf("\n");
  printf("Nombre de mouvements effectués : %d \n",game_nb_moves(g));
  printf("\n");
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
  printf("********************\n");
  for(int yt=GAME_SIZE-1; yt>=0; yt--){
    printf("%d ",yt);
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
  printf("  ");
  for(int k=0;k<GAME_SIZE;k++) printf(" %d ",k);
  printf("\n\n");
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
    if(atoi(num)<0 || atoi(num)>=nbPiece){
      printf("Choisissez parmis les propositions..\n");
      continue;
    }
    if (strcmp(num,"q\n")==0){
      exit(EXIT_SUCCESS);
    }
    int num_real=atoi(num);
    if(is_horizontal(game_piece(g,num_real))){
      printf("Quelle direction? left/right ?\n");
      vert=false;
    }
    else {
      printf("Quelle direction? up/down ?\n");
      vert=true;
    }
    fgets(dir_str,7,stdin);
    bool test=true;
    if (strcmp(dir_str,"q\n")==0){
      exit(EXIT_SUCCESS);
    }
    else if (strcmp(dir_str,"left\n")==0 && !vert){
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
    if (strcmp(distance,"q\n")==0){
      exit(EXIT_SUCCESS);
    }
    bool goodMove=play_move(g,num_real,direction,atoi(distance));
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



int main(int argc,char *argv[]){
  printf("choisissez le nombre de voiture\n que vous souhaitez\n Maximum 9\n");
  char rejouer[6];
  if(argc!=2) usage(argv[0]);
  int nbPiece = atoi(argv[1]);
  if(nbPiece<=0 || nbPiece>PIECE_MAX) usage(argv[0]);
  piece* grille = creerPieces(nbPiece);
  game rushHour = new_game_hr(nbPiece,grille);
  affichage((cgame)rushHour);
  startGame(rushHour,nbPiece);
  printf("Voulez vous rejouez? oui/non \n");
  fgets(rejouer,6,stdin);
  while(strcmp(rejouer,"oui\n")==0){
    piece* grille = creerPieces(nbPiece);
    game rushHour = new_game_hr(nbPiece,grille);
    affichage((cgame)rushHour);
    startGame(rushHour,nbPiece);
    printf("Voulez vous rejouez? oui/non \n");
    fgets(rejouer,6,stdin);
  }
}  
