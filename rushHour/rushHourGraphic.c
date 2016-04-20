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
#define WINDOW_SIZE 600


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


  
  /* SDL_Renderer *menu = SDL_CreateRenderer(screen,-1, SDL_RENDERER_ACCELERATED|SDL_RENDERER_TARGETTEXTURE);
  if (menu == NULL){
    printf("NTMMTN");
  }
  */
  
  SDL_Rect menu_pos= {0, 0, WINDOW_SIZE, WINDOW_SIZE};
  /*SDL_Texture *texture_menu = IMG_LoadTexture(menu,"RushHourMenu.png");
  if (texture_menu == NULL){
    printf("NTM");
  }

  SDL_RenderClear(menu);
  SDL_RenderCopy(menu, texture_menu, NULL, &menu_pos);
  SDL_RenderPresent(menu);
  */
  SDL_Surface *screen_surf = SDL_GetWindowSurface(screen);
  SDL_Surface *menu_surf = IMG_Load("../../rushHour/RushHourMenu.png");
  SDL_BlitSurface(menu_surf, NULL, screen_surf, &menu_pos);
  SDL_UpdateWindowSurface(screen);

  
  while(continuer){
    SDL_WaitEvent(&event);
    if(event.type == SDL_QUIT){
      continuer=false;
      SDL_DestroyWindow(screen);
      //SDL_DestroyRenderer(menu);
      SDL_Quit();
    }
  }
  return EXIT_SUCCESS;
}
