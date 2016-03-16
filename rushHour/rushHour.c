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
#define valeurCaseVide -1

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

void initialisation_affichage(cgame g,int nb,int tab_game[GAME_SIZE][GAME_SIZE]){
  for(int i=0; i<GAME_SIZE; i++){
    for(int j=0; j<GAME_SIZE; j++){
      tab_game[i][j]= valeurCaseVide;
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
}

void remplissage_affichage(cgame g,int nb,int tab_game[GAME_SIZE][GAME_SIZE]){
  for(int yt=GAME_SIZE-1; yt>=0; yt--){
    printf("%d ",yt);
    for(int xt=0; xt<GAME_SIZE; xt++){
      if(tab_game[xt][yt]==valeurCaseVide){
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
}

void affichage(cgame g){
  printf("\n");
  printf("Nombre de mouvements effectués : %d \n",game_nb_moves(g));
  printf("\n");
  int nb = game_nb_pieces(g);
  int tab_game[GAME_SIZE][GAME_SIZE];
  initialisation_affichage(g,nb,tab_game);
  printf("********************\n");
  remplissage_affichage(g,nb,tab_game);
  printf("Pour quitter appuyez sur q \n");
  printf("\n");
}

bool string_to_dir(dir *d,char *dir_str,bool vert){
  bool res=true;
  if (strcmp(dir_str,"left\n")==0 && !vert){
    *d=LEFT;
  }
  else if (strcmp(dir_str,"right\n")==0 && !vert){
    *d=RIGHT;
  }
  else if (strcmp(dir_str,"up\n")==0 && vert){
    *d=UP;
  }
  else if (strcmp(dir_str,"down\n")==0 && vert){
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

int choose_number_piece(int nbPiece){
  char num_str[3];
  bool good_num = false;
  int num;
  while(!good_num){
    good_num = true;
    printf("Numéro de la piece à bouger ?\n");
    for(int a=0;a<nbPiece;a++) printf(" %d",a);
    printf("\n");
    fgets(num_str,3,stdin);
    if (wantToQuit(num_str)==true){
      exit(EXIT_SUCCESS);
    }
    num=atoi(num_str);
    if(num<0 || num>=nbPiece){
      printf("Choisissez parmis les propositions..\n");
      good_num = false;
    }
  }
  return num;
}



int choose_distance(){
  char distance[3];
  printf("La distance?\n");
  fgets(distance,3,stdin);
  if (wantToQuit(distance)==true){
    exit(EXIT_SUCCESS);
  }
  int dist = atoi(distance);
  return dist;
}

bool choose_direction(cgame g,int num_piece,dir *direction){
  char dir_str[7];
  bool vert;
  if(is_horizontal(game_piece(g,num_piece))){
      printf("Quelle direction? left/right ?\n");
      vert=false;
    }
  else {
      printf("Quelle direction? up/down ?\n");
      vert=true;
  }
  fgets(dir_str,7,stdin);
  if (wantToQuit(dir_str)==true){
    exit(EXIT_SUCCESS);
  }
  if (string_to_dir(direction,dir_str,vert)==false){
    printf("Choisissez parmis les propositions..\n");
    return false;
  }
  return true;
}


void startGame(game g,int nbPiece){
  while(!game_over_hr(g)){
    dir direction;
    int num = choose_number_piece(nbPiece);
    int test = choose_direction(g,num,&direction);
    if (!test) continue;
    int distance = choose_distance();
    bool goodMove=play_move(g,num,direction,distance);
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

bool play(int nbPieces){
  char rejouer[6];
  piece* grille = creerPieces(nbPieces); ;
  game rushHour = new_game_hr(nbPieces,grille);
  affichage((cgame)rushHour);
  startGame(rushHour,nbPieces); 
  printf("Voulez vous rejouez? oui/non \n");
  fgets(rejouer,6,stdin);
  if(strcmp(rejouer,"oui\n")==0)return true;
  else return false;
}

void play_Replay(bool replay,int nbPieces){
  while(replay==true){
    replay=play(nbPieces);
  }
}

int main(int argc,char *argv[]){
  bool replay=true;
  if(argc!=2) usage(argv[0]);
  int nbPieces = atoi(argv[1]);
  if(nbPieces<=0 || nbPieces>PIECE_MAX) usage(argv[0]);
  play_Replay(replay,nbPieces);
  return EXIT_SUCCESS;
}  
