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
#include "displaySDL.h"
#define WINDOW_SIZE 800
//Constantes rushHour.c
#define PIECE_MAX 9
#define SMALL_SIZE 2
#define BIG_SIZE 3
#define GAME_SIZE 6
#define EMPTY_CASE_VALUE -1

/*
  Retourne le nombre de coups minimum du game ou -1 si le game n'est pas solvable. Affiche une fenetre de chargement en attendant la valeur de retour
*/

int solver_time(game g){
  int solvable = 0;
  graph solutions = create_graph(g, true,&solvable);
  int res;
  if(solvable == -1) res= -1;
  else res = simple_search(solutions);
  return res;
}

int is_valid_game(game g,bool isRandom){
  int res;
  if(isRandom){
    SDL_Window *screen;
    screen = SDL_CreateWindow("Loading...", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 400, 200, SDL_WINDOW_SHOWN);
    if(screen == NULL){
      erreur_window();
      SDL_Quit();
      exit(EXIT_FAILURE);
    }
    SDL_Renderer *renderer = SDL_CreateRenderer(screen,-1, SDL_RENDERER_ACCELERATED|SDL_RENDERER_TARGETTEXTURE);
    if (renderer == NULL){
      erreur_renderer();
    }
    SDL_Surface *sprite ;
    sprite = IMG_Load("../../rushHour/Images/loadingSolveur.bmp");
    SDL_Texture *texture= SDL_CreateTextureFromSurface(renderer,sprite);
    SDL_Rect pos= {0, 0, 400, 200};
    SDL_RenderCopy(renderer, texture, NULL, &pos);
    SDL_RenderPresent(renderer);
    //calcul 
    res = solver_time(g);
    //destruction de la fenêtre
    SDL_RenderPresent(renderer);
    SDL_FreeSurface(sprite);
    SDL_DestroyTexture(texture);
    SDL_DestroyWindow(screen);
  }
  else res = solver_time(g);
  return res;
}

/*
Renvoie true si le point (x,y) est dans le rectangle de coin supérieur (rectX,rectY) et de taille w*h 
 */

bool in_rectangle(int x,int y,int rectX, int rectY,int w,int h){
  int tmpX= rectX+w;
  int tmpY= rectY+h;
  return x>rectX && x<tmpX && y>rectY && y<tmpY; 
}

/*
  Renvoie le numéro de la pièce g par rapport aux coordonnées de la fenetre SDL
 */
int graphic_position_to_piece(cgame g,int x,int y){
  int newX = (x-100)/100;
  int newY = 5-(y-100)/100;
  return game_square_piece((game)g,newX,newY);
}

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
  
  while(continuer){
    continuer=title_screen_display(renderer);
  }
 
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(screen);
  SDL_Quit();
  return EXIT_SUCCESS;
}
