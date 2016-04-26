#ifndef DISPLAYSDL
#define DISPLAYSDL
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "config_sdl.h"

void game_display(SDL_Renderer *renderer, cgame g,int solveur,int indSelec);
bool title_screen_display(SDL_Renderer *renderer);
void board_display(SDL_Renderer *renderer);
void display_nb_mov(SDL_Renderer *renderer,int nb_mov_solver,int nb_mov_game);
void erreur_window();
void erreur_renderer();

#endif
