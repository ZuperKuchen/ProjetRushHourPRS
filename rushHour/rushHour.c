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
#define EMPTY_CASE_VALUE -1

static void usage(char *commande){
  fprintf(stderr," %s <entier> nombre de pieces <=9 \n",commande);
  exit(EXIT_FAILURE);
}

int random(int max){
    int nombre_aleatoire;
    nombre_aleatoire = rand()%max;
    return nombre_aleatoire;
}


void possible_cases(bool small,bool horizontal,int *x,int *y){
  if(horizontal){ 
    if(small){
      *x=random(5);                                  /* en fonction de si la piece est small/big et horizontal/vertical*/
    }                                                /* on génère aléatoirement des valeurs x et y en fonction des cas possibles */
    else{
      *x=random(4);
    }
    *y=random(6);
  }
  else{
    if(small){
      *y=random(5);
    }
    else{
      *y=random(4);
    }
    *x=random(6);
  }
}


bool random_bool(void){                                /* random_bool génère un nombre aleatoire entre 0 et 9 compris,soit 10 nombres*/ 
  int nombre_aleatoire = rand()%10;                    /* si le nombre est 0,1,2,3 ou 4, random_bool renvoie true, false sinon*/
  if(nombre_aleatoire<5) return true;
  else return false;
}


bool test_unsolvable(piece p1,piece p2){               /* test_unsolvable regarde quelques cas particuliers impossibles à résoudre*/
  if(get_y(p1)==get_y(p2)){                            /* pour le joueur */
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

piece* array_pieces(int nombrePiece){
  piece* tab =(piece*)malloc(nombrePiece * sizeof(piece));
  srand(time(NULL));
  tab[0]=new_piece_rh(0,3,true,true);
  for(int i=1;i<nombrePiece;i++){
    bool small = random_bool();
    bool horizontal = random_bool();
    int x;
    int y;      
    possible_cases(small,horizontal,&x,&y);
    tab[i]=new_piece_rh(x,y,small,horizontal);                /* on creer la piece i et on la met dans le tableaux de pieces */
    if((get_y(tab[i])==3) && is_horizontal(tab[i])){          /* on verifie qu'elle n'est pas horizontal avec y=3 */
      delete_piece(tab[i]);
      i--;
      continue;                                               /* si erreur on re-crée la piece */
    }
    int j=0;  
    for(j=0;j<i;j++){
      if (!test_unsolvable(tab[i],tab[j])) break;
      else if((intersect((cpiece)tab[i],(cpiece)tab[j])==false)){
	continue;
      }
      else{
	break;
      }
    }
    if(j!=i){                                                /* de meme ici si intersection */
      delete_piece(tab[i]);
      i--;
      continue;
    }
  }
  return tab;
}

void display_init(cgame g,int nb,int tab_game[GAME_SIZE][GAME_SIZE]){
  for(int i=0; i<GAME_SIZE; i++){
    for(int j=0; j<GAME_SIZE; j++){
      tab_game[i][j]= EMPTY_CASE_VALUE;
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

void display_cases(cgame g,int nb,int tab_game[GAME_SIZE][GAME_SIZE]){
  for(int yt=GAME_SIZE-1; yt>=0; yt--){
    printf("%d ",yt);
    for(int xt=0; xt<GAME_SIZE; xt++){
      if(tab_game[xt][yt]==EMPTY_CASE_VALUE){
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

void display(cgame g){
  printf("\n");
  printf("Nombre de mouvements effectués : %d \n",game_nb_moves(g));
  printf("\n");
  int nb = game_nb_pieces(g);
  int tab_game[GAME_SIZE][GAME_SIZE];
  display_init(g,nb,tab_game);
  printf("********************\n");
  display_cases(g,nb,tab_game);
  printf("| Pour quitter appuyez sur q |\n");
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

bool want_to_quit(char *dir_str){
  if (strcmp(dir_str,"q\n")==0){
    return true;
  }
  return false;
}

int choose_number_piece(int nbPiece, game g){
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



int choose_distance(game g){
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

bool choose_direction(game g,int num_piece,dir *direction){
  char dir_str[7];
  bool vert;
  if(is_horizontal(game_piece((cgame)g,num_piece))){
      printf("Quelle direction ? left/right ?\n");
      vert=false;
    }
  else {
      printf("Quelle direction ? up/down ?\n");
      vert=true;
  }
  fgets(dir_str,7,stdin);
  if (want_to_quit(dir_str)==true){
    delete_game(g);
    exit(EXIT_SUCCESS);
  }
  if (string_to_dir(direction,dir_str,vert)==false){
    printf("Choisissez parmis les propositions..\n");
    return false;
  }
  return true;
}


void start_game(game g,int nbPiece){
  while(!game_over_hr(g)){
    dir direction;
    int num = choose_number_piece(nbPiece,g);
    int test = choose_direction(g,num,&direction);
    if (!test) continue;
    int distance = choose_distance(g);
    bool goodMove=play_move(g,num,direction,distance);
    if (goodMove==false) {
      printf("\n! Déplacement impossible !\n\n");
      continue;
    }
    printf("___________________________________________ \n");
    display(g);
  }
  printf("Bravo ! le jeu est terminé\n ");
  printf("___________________________________________ \n");
}

bool play(int nbPieces){
  char rejouer[6];
  piece* grille = array_pieces(nbPieces); ;
  game rushHour = new_game_hr(nbPieces,grille);
  display((cgame)rushHour);
  start_game(rushHour,nbPieces); 
  delete_game(rushHour);
  printf("Voulez vous rejouer ? oui/non \n");
  fgets(rejouer,6,stdin);
  if(strcmp(rejouer,"oui\n")==0)return true;
  else return false;
}

void play_replay(bool replay,int nbPieces){
  while(replay==true){
    replay=play(nbPieces);
  }
}

int main(int argc,char *argv[]){
  bool replay=true;
  if(argc!=2) usage(argv[0]);
  int nbPieces = atoi(argv[1]);
  if(nbPieces<=0 || nbPieces>PIECE_MAX) usage(argv[0]);
  play_replay(replay,nbPieces);
  return EXIT_SUCCESS;
}  
