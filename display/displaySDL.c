#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "game.h"
#include "piece.h"
#include "string.h"
#include "solveur.h"
#include "graph.h"
#include "displaySDL.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "config_sdl.h"
#include "rushHour.h"
#define WINDOW_SIZE 800

void erreur_window(){
  fprintf(stderr, "Erreur d'initialisation de la fenetre : %s\n", SDL_GetError());
}

void erreur_renderer(){
  fprintf(stderr, "Erreur d'initialisation du renderer : %s\n", SDL_GetError());
}

void game_display(SDL_Renderer *renderer, cgame g,int best_play,int indSelec){
  SDL_RenderClear(renderer);
  board_display(renderer);
  int nb_pieces=game_nb_pieces(g);
  SDL_Rect pos={0,0,0,0};
  SDL_Surface *sprite;
  SDL_Texture *texture;
  bool selec = false;
  for (int i=0; i<nb_pieces ; i++){
    if(indSelec == i) selec = true;
    else selec = false;
    cpiece tmp= game_piece(g, i);
    piece_graphic_position(&pos,tmp);
    sprite = piece_to_sprite(tmp,i,selec);
    texture = SDL_CreateTextureFromSurface(renderer,sprite);
    SDL_RenderCopy(renderer, texture, NULL, &pos);
    SDL_FreeSurface(sprite);
    SDL_DestroyTexture(texture);
  }
  SDL_RenderPresent(renderer);
  display_nb_mov(renderer,best_play,game_nb_moves(g));
}


bool title_screen_display(SDL_Renderer *renderer){
  SDL_Surface *sprite = IMG_Load("../../rushHour/Images/titleScreen.bmp");
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
	    return play_graphic(renderer,true);
	    stop = true;
	    break;
	  }
	  if(event.button.y > 300 && event.button.y < 370){
	    return play_graphic(renderer,false);
	    stop = true;
	    break;
	  }
	  if(event.button.y > 400 && event.button.y < 470){
	    stop=true;
	    return false;
	    break;
	  }
	}
      case SDL_QUIT:
	return false;
	break;
      default:
	break;
      }	
    }
  }
  return true;
}

void board_display(SDL_Renderer *renderer){
  SDL_Surface *sprite = IMG_Load("../../rushHour/Images/FondRH.bmp");
  SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer,sprite);
  SDL_FreeSurface(sprite);
  SDL_Rect pos= {0, 0, WINDOW_SIZE, WINDOW_SIZE};
  SDL_RenderCopy(renderer, texture, NULL, &pos);
  SDL_DestroyTexture(texture);
  SDL_RenderPresent(renderer);
}

void display_nb_mov(SDL_Renderer *renderer,int nb_mov_solver,int nb_mov_game){
  SDL_Surface *texte1 = NULL;
  SDL_Surface *texte2 = NULL;
  TTF_Font *police = NULL;
  SDL_Color color = {0,0,0};
  if(TTF_Init() == -1){
    fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
    exit(EXIT_FAILURE);
  }
  police = TTF_OpenFont("../../rushHour/Images/pricedownbl.ttf",32);
  char path1[10] = {'\0'};
  int numb = nb_mov_solver%10;
  nb_mov_solver/=10;
  char n1[4];
  char premier = (char) numb + 48;
  n1[0] = premier;
  char path2[10] = {'\0'};
  int numb2 = nb_mov_game%10;
  char n2[4];
  nb_mov_game/=10;
  char premier2 = (char) numb2 + 48;
  n2[0] = premier2;
  int compt = 1;
  while(nb_mov_solver>0){
    numb = nb_mov_solver%10;
    char tmp = (char) numb + 48;
    n1[compt] = tmp;
    nb_mov_solver/=10;
    compt++;
  }
  n1[compt]='\0';
  strcat(path1,n1);
  for(int i=0;i<compt/2;i++){
    char tmp = path1[i];
    path1[i] = path1[compt-1-i];
    path1[compt-1-i] = tmp;
  }
  
  compt = 1;
  while(nb_mov_game>0){
    numb2 = nb_mov_game%10;
    char tmp = (char) numb2 + 48;
    n2[compt] = tmp;
    nb_mov_game/=10;
    compt++;
  }
  n2[compt]='\0';
  strcat(path2,n2);
  for(int i=0;i<compt/2;i++){
    char tmp = path2[i];
    path2[i] = path2[compt-1-i];
    path2[compt-1-i] = tmp;
  }  
  texte1 = TTF_RenderText_Blended(police, path1, color);
  texte2 = TTF_RenderText_Blended(police, path2, color);
  SDL_Texture *texture1 = SDL_CreateTextureFromSurface(renderer,texte1);
  SDL_Texture *texture2 = SDL_CreateTextureFromSurface(renderer,texte2);
  SDL_FreeSurface(texte1);
  SDL_FreeSurface(texte2);
  SDL_Rect pos1= {290, 20, 40, 40};
  SDL_Rect pos2= {750, 20, 40, 40};
  SDL_RenderCopy(renderer, texture1, NULL, &pos1);
  SDL_RenderCopy(renderer, texture2, NULL, &pos2);
  SDL_DestroyTexture(texture1);
  SDL_DestroyTexture(texture2);
  SDL_RenderPresent(renderer);
  TTF_CloseFont(police);
  TTF_Quit();
}	  
