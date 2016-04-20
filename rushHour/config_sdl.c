#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include "config_sdl.h"
/*
bool config_sdl(SDL_Window *screen){
  SDL_Event evenements;
  if(SDL_Init(SDL_INIT_VIDEO) < 0){
    fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
    SDL_Quit();
    return false;
  }
  screen = SDL_CreateWindow("X-TREM RushHour !!!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 600, SDL_WINDOW_SHOWN);
  if(screen == NULL){
    fprintf(stderr, "Erreur d'initialisation de la fenetre : %s\n", SDL_GetError());
    SDL_Quit();
    return false;
  }
  return true;
}

bool quit_sdl(SDL_Window *screen){
  SDL_DestroyWindow(screen);
  SDL_Quit();
  return true;
*/
