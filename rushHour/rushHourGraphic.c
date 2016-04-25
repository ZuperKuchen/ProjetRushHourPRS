#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include "game.h"
#include "piece.h"
#include "string.h"
#include "rushHour.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "config_sdl.h"
#include "solveur.h"
#include "graph.h"
#define WINDOW_SIZE 800
//Constantes rushHour.c
#define PIECE_MAX 9
#define SMALL_SIZE 2
#define BIG_SIZE 3
#define GAME_SIZE 6
#define EMPTY_CASE_VALUE -1

void board_display(SDL_Renderer *renderer);
game create_valid_game(int nb_pieces, int* best_play);
int choose_nb_pieces(void);
int is_valid_game(game g);
void make_move(game g);


void piece_graphic_position(SDL_Rect *pos_piece, cpiece p){
  pos_piece->x=get_x(p)*100 +100;
  pos_piece->y=(6-get_y(p)-get_height(p))*100 +100;
  pos_piece->w=get_width(p)*100;
  pos_piece->h=get_height(p)*100;
}

SDL_Surface* piece_to_sprite(cpiece p, int ind){
  if (ind == 0){
    return IMG_Load("../../Images/redCar.png");
  }
  else{
    if (is_horizontal(p)){
      if(get_height(p)==3){
	return IMG_Load("../../Images/carRight3.png");
      }
      else{
	return IMG_Load("../../Images/carRight2.png");
      }
    }
    else if (get_width(p)==2){
      return IMG_Load("../../Images/carUp2.png");
    }
    else {
      return IMG_Load("../../Images/carUp3.png");
    }
  }
}

void game_display(SDL_Renderer *renderer, cgame g){
  SDL_RenderClear(renderer);
  board_display(renderer);
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
  }
  SDL_RenderPresent(renderer);
}

bool title_screen_display(SDL_Renderer *renderer){
  SDL_Surface *sprite = IMG_Load("../../Images/titleScreen.bmp");
  SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, sprite);
  SDL_FreeSurface(sprite);
  SDL_Rect pos= {0, 0, WINDOW_SIZE, WINDOW_SIZE};
  SDL_RenderCopy(renderer, texture, NULL, &pos);
  SDL_DestroyTexture(texture);
  SDL_RenderPresent(renderer);
  bool stop = false;
  SDL_Event event;
  while(!stop){
    while (SDL_PollEvent(&event)){
      switch (event.type){
      case SDL_MOUSEBUTTONUP:
	if(event.button.x > 100 && event.button.x < 300){
	  if(event.button.y > 200 && event.button.y < 270){
	    board_display(renderer); // A remplacer par play
	    stop = true;
	  }
// AJOUT DES BOUTONS QUITTER ET JOUER CONFIG DEJA ENREGISTREES
	}
      	break;
      case SDL_QUIT:
	stop=true;
	break;
      default:
	break;
      }	
    }
  }
}

void board_display(SDL_Renderer *renderer){
  SDL_Surface *sprite = IMG_Load("../../Images/FondRH.bmp");
  SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer,sprite);
  SDL_FreeSurface(sprite);
  SDL_Rect pos= {0, 0, WINDOW_SIZE, WINDOW_SIZE};
  SDL_RenderCopy(renderer, texture, NULL, &pos);
  SDL_DestroyTexture(texture);
  SDL_RenderPresent(renderer);
}

void play_graphic(SDL_Renderer *renderer){
  board_display(renderer);
  int nb_pieces=choose_nb_pieces();
  int best_play=0;
  game g = create_valid_game(nb_pieces, &best_play);
  game_display(renderer,g);
  /*bool win=false;
  while(!win){
    make_move(g);
    board_display(renderer,g);
    win=is_game_over_rh(g);
    
    }*/
}

game create_valid_game(int nb_pieces, int* best_play){
  bool end=false;
  game g;
  while (!end){
    piece* grille = array_pieces(nb_pieces); 
    game tmp = new_game_hr(nb_pieces,grille);
    *best_play=is_valid_game(tmp);
    if ( *best_play > 8){
      end=true;
      g=tmp;
    }
    else delete_game(tmp);
  }
  return g; 
}

//A COMPLETER
int choose_nb_pieces(void){
  return 6;
}
//A COMPLETER PAR PIERRE
int is_valid_game(game g){
  int solvable = 0;
  graph solutions = create_graph(g, true,&solvable);
  if(solvable == -1) return -1;
  else return simple_search(solutions);
}

void make_move(game g){
    
  
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
 
  /*piece* grille = array_pieces(6); 
  game g = new_game_hr(6,grille);
  game_display(renderer,(cgame)g);
  */
  play_graphic(renderer);
 
 
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
