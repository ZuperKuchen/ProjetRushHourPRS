#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include "game.h"
#include "piece.h"
#include "string.h"
#include "rushHourGraphic.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "config_sdl.h"
#define WINDOW_SIZE 800
//Constantes rushHour.c
#define PIECE_MAX 9
#define SMALL_SIZE 2
#define BIG_SIZE 3
#define GAME_SIZE 6
#define EMPTY_CASE_VALUE -1

void piece_graphic_position(SDL_Rect *pos_piece, cpiece p){
  pos_piece->x=get_x(p)*100 +100;
  pos_piece->y=(6-get_y(p)-get_height(p))*100 +100;
  pos_piece->w=get_width(p)*100;
  pos_piece->h=get_height(p)*100;
}

SDL_Surface* piece_to_sprite(cpiece p, int ind){
  if (ind == 0){
    return IMG_Load("../../rushHour/carRight2.png");
  }
  else{
    if (is_horizontal(p)){
      if(get_height(p)==3){
	return IMG_Load("../../rushHour/carRight3.png");
      }
      else{
	return IMG_Load("../../rushHour/carRight2.png");
      }
    }
    else if (get_width(p)==2){
      return IMG_Load("../../rushHour/carUp2.png");
    }
    else {
      return IMG_Load("../../rushHour/carUp3.png");
    }
  }
}

void cars_display(SDL_Renderer *renderer, cgame g){
  int nb_pieces=game_nb_pieces(g);
  SDL_Rect pos={0,0,0,0};
  SDL_Surface *sprite;
  SDL_Texture *texture;
  for (int i=0; i<nb_pieces ; i++){
    cpiece tmp= game_piece(g, i);
    piece_graphic_position(&pos,tmp);
    sprite = piece_to_sprite(tmp,i);
    texture = SDL_CreateTextureFromSurface(renderer,sprite);
    SDL_RenderCopy(renderer, texture, NULL, &pos);
    SDL_FreeSurface(sprite);
    SDL_DestroyTexture(texture);
    //SDL_RenderPresent(renderer);
  }
  SDL_RenderPresent(renderer);
}

void title_screen_display(SDL_Renderer *renderer){
  SDL_Surface *sprite = IMG_Load("../../rushHour/titleScreen.jpg");
  SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer,sprite);
  SDL_FreeSurface(sprite);
  SDL_Rect pos= {0, 0, WINDOW_SIZE, WINDOW_SIZE};
  SDL_RenderCopy(renderer, texture, NULL, &pos);
  SDL_DestroyTexture(texture);
  SDL_RenderPresent(renderer);
}

void board_display(SDL_Renderer *renderer){
  SDL_Surface *sprite = IMG_Load("../../rushHour/FondRH.bmp");
  SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer,sprite);
  SDL_FreeSurface(sprite);
  SDL_Rect pos= {0, 0, WINDOW_SIZE, WINDOW_SIZE};
  SDL_RenderCopy(renderer, texture, NULL, &pos);
  SDL_DestroyTexture(texture);
  SDL_RenderPresent(renderer);
}

// Pris dans solveur.c

void create_grid(FILE *file,int nbPieces,piece *tableau){
  int line[20];
  for(int i=0; i<nbPieces; i++){
    bool can_move_x,can_move_y;
    fscanf(file,"%d %d %d %d %d %d",&line[0],&line[1],&line[2],&line[3],&line[4],&line[5]);
    if(line[4]==0) can_move_x = false;
    else can_move_x = true;
    if(line[5]==0) can_move_y = false;
    else can_move_y = true;
    tableau[i] = new_piece(line[0],line[1],line[2],line[3],can_move_x,can_move_y); 
  }
}

//Pris dans rushHour.c
int random(int max){
    int nombre_aleatoire;
    nombre_aleatoire = rand()%max;
    return nombre_aleatoire;
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

/*
void start_game_graphic(game g,int nbPiece, ){
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
    display(g);
  }
}
*/

int main(int argc,char **argv){
  SDL_Window *screen = NULL;
  SDL_Event event;
  bool continuer = true;
  //Initialisation
  if(SDL_Init(SDL_INIT_VIDEO) < 0){
    fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
    SDL_Quit();
    return EXIT_FAILURE;
  }
  if(IMG_Init(IMG_INIT_PNG) <0){
    printf("erreur IMG_Init: %s\n", SDL_GetError());
    SDL_Quit();
    IMG_Quit();
    return EXIT_FAILURE;
  }
  screen = SDL_CreateWindow("X-TREM RushHour !!!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_SIZE, WINDOW_SIZE, SDL_WINDOW_SHOWN);
  if(screen == NULL){
    fprintf(stderr, "Erreur d'initialisation de la fenetre : %s\n", SDL_GetError());
    SDL_Quit();
    return EXIT_FAILURE;
  }
  SDL_Renderer *renderer = SDL_CreateRenderer(screen,-1, SDL_RENDERER_ACCELERATED|SDL_RENDERER_TARGETTEXTURE);
  if (renderer == NULL){
    fprintf(stderr, "Erreur d'initialisation du renderer : %s\n", SDL_GetError());
  }


  //Ecran Titre
  title_screen_display(renderer);
 
  SDL_Delay(3000);
  SDL_RenderClear(renderer);

  board_display(renderer);
  //piece t_pieces[6]; //= malloc(6*sizeof(piece));
  //FILE *niveau = fopen("../../rushHour/rushHour.txt","r");
  // create_grid(niveau,6,t_pieces);
  
  piece* grille = array_pieces(6); ;
  game g = new_game_hr(6,grille);
  cars_display(renderer,(cgame)g);
  
  /*SDL_Surface *sprite = IMG_Load("../../rushHour/redCar.png");
  SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer,sprite);
  SDL_Rect pos = {0,0,0,0};
  piece p = new_piece_rh(0, 3, true, true);
  piece_graphic_position(&pos,(cpiece) p);
  SDL_RenderCopy(renderer,texture, NULL,&pos);
  SDL_RenderPresent(renderer);
  SDL_Delay(1000);
  SDL_Rect pos2= {300,300,200,100};
  SDL_RenderCopy(renderer,texture, NULL, &pos2);
  SDL_RenderPresent(renderer);
  */
  
 
  //FinTest
  while(continuer){
    SDL_WaitEvent(&event);
    if(event.type == SDL_QUIT){
      continuer=false;
      SDL_DestroyRenderer(renderer);
      SDL_DestroyWindow(screen);
      SDL_Quit();
    }
  }
  return EXIT_SUCCESS;
}
