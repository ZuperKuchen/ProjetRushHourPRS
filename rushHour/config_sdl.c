#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include "config_sdl.h"

int config_sdl(){
  SDL_Window* fenetre;
  SDL_Event evenements;
  bool terminer = true;
  if(SDL_Init(SDL_INIT_VIDEO) < 0){
    fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
    exit(EXIT_FAILURE);
    SDL_Quit();
    return -1;
  }
  fenetre = SDL_CreateWindow("Test SDL 2.0", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 600, SDL_WINDOW_SHOWN);
  if(fenetre == 0){
    fprintf(stderr, "Erreur d'initialisation de la fenetre : %s\n", SDL_GetError());
    exit(EXIT_FAILURE);
    SDL_Quit();
    return -1;
  }
  if(terminer) SDL_Delay(3000); 
  SDL_DestroyWindow(fenetre);
  SDL_Quit();
  return 0;
}
