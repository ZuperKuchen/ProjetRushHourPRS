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

void pieces_graphic_position(SDL_Rect **pos_pieces, piece pieces[],int nb_pieces){
  for (int i=0; i<nb_pieces; i++){
    pos_pieces[i]->x=get_x((cpiece) pieces[i]) * 100 + 100;
    pos_pieces[i]->y=(- get_y((cpiece) piece[i]) + 6) * 100 + 100;
    pos_pieces[i]->w=get_width((cpiece) piece[i])*100;
    pos_pieces[i]->h=get_height((cpiece) piece[i])*100;
  }
}

bool cars_display(SDL_Renderer renderer,game g){
  int nb_pieces=game_nb_pieces(g);
  SDL_Rect **pos_pieces;
  piece_graphic_position(SDL_Rect pos_pieces, , 
  




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
  SDL_Renderer *menu_renderer = SDL_CreateRenderer(screen,-1, SDL_RENDERER_ACCELERATED|SDL_RENDERER_TARGETTEXTURE);
  if (menu_renderer == NULL){
    fprintf(stderr, "Erreur d'initialisation du renderer : %s\n", SDL_GetError());
  }
  SDL_Surface *menu_sprite = IMG_Load("../../rushHour/titleScreen.jpg");
  SDL_Texture *menu_texture = SDL_CreateTextureFromSurface(menu_renderer,menu_sprite);
  SDL_FreeSurface(menu_sprite);
  SDL_Rect menu_pos= {0, 0, WINDOW_SIZE, WINDOW_SIZE};
  SDL_RenderCopy(menu_renderer, menu_texture, NULL, &menu_pos);
  SDL_RenderPresent(menu_renderer);
  //if (texture_menu == NULL){
  





  //FinTest
  while(continuer){
    SDL_WaitEvent(&event);
    if(event.type == SDL_QUIT){
      continuer=false;
      SDL_DestroyRenderer(menu_renderer);
      SDL_DestroyWindow(screen);
      SDL_Quit();
    }
  }
  return EXIT_SUCCESS;
}
