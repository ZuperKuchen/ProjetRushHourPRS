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

/*
renvoi le game enregistré correspondant à l'indice level
 */
game init_config_text(int level){
  char path[30] = "../../rushHour/file/rushHour";
  char number = (char) level+48;
  char* txt = ".txt";
  char n[3];
  n[0] = number;
  n[1] = '\0';
  strcat(path,n);
  strcat(path,txt);
  FILE *file= fopen(path,"r");
  int width, height, nb_pieces;
  piece* grid= read_Config_txt(file, &width, &height, &nb_pieces);
  game g=new_game(width, height, nb_pieces, grid);
  return g;
}

/*
modifie le SDL_Rect passé en paramètre en lui donnant les coordonnées sur la fenêtre SDL de la pièce en paramètre
*/
void piece_graphic_position(SDL_Rect *pos_piece, cpiece p){
  pos_piece->x=get_x(p)*100 +100;
  pos_piece->y=(6-get_y(p)-get_height(p))*100 +100;
  pos_piece->w=get_width(p)*100;
  pos_piece->h=get_height(p)*100;
}

/*
  retourne le sprite correspondant à cpièce suivant sa taille, sa direction, si elle est selctionnée ou non ... 
*/
SDL_Surface* piece_to_sprite(cpiece p, int ind, bool select){
  if (ind == 0){
    if(select) return IMG_Load("../../rushHour/Images/gCarRight2.png");
    return IMG_Load("../../rushHour/Images/redCar.png");
  }
  else{
    if (is_horizontal(p)){
      if(get_height(p)==3){
	if(select) return IMG_Load("../../rushHour/Images/gCarRight3.png");
	return IMG_Load("../../rushHour/Images/carRight3.png");
      }
      else{
	if(select) return IMG_Load("../../rushHour/Images/gCarRight2.png");
	return IMG_Load("../../rushHour/Images/carRight2.png");
      }
    }
    else if (get_width(p)==2){
      if(select) return IMG_Load("../../rushHour/Images/gCarUp2.png");
      return IMG_Load("../../rushHour/Images/carUp2.png");
    }
    else {
      if(select) return IMG_Load("../../rushHour/Images/gCarUp3.png");
      return IMG_Load("../../rushHour/Images/carUp3.png");
    }
  }
}


bool play_graphic(SDL_Renderer *renderer,bool is_random){
  board_display(renderer);
  int best_play=0;
  int chose_number=0;
  game g;
  if (is_random){
    chose_number= make_choice(is_random);
    g = create_valid_game(chose_number, &best_play);
  }
  else {
    chose_number= make_choice(is_random);
    g = init_config_text(chose_number);
    best_play=is_valid_game(g);
  }
  game_display(renderer,g,best_play,-1);
  bool win=false;
  while(!win){
    if(!make_move(renderer,g,best_play)) return false;
    game_display(renderer,g,best_play,-1);
    win=game_over_hr(g);
  }
  return want_to_replay();
}

bool want_to_replay(void){
  SDL_Window *screen;
  screen = SDL_CreateWindow("Rejouer ?", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 400, 200, SDL_WINDOW_SHOWN);
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
  sprite = IMG_Load("../../rushHour/Images/endGame.bmp");
  SDL_Texture *texture= SDL_CreateTextureFromSurface(renderer,sprite);
  SDL_Rect pos= {0, 0, 400, 200};
  SDL_RenderCopy(renderer, texture, NULL, &pos);
  SDL_RenderPresent(renderer);
  SDL_Event event;
  bool end=false;
  bool res;
  while(!end){
    while (SDL_PollEvent(&event)){
      switch(event.type){
      case SDL_MOUSEBUTTONUP:
	if(in_rectangle(event.button.x,event.button.y,150,135,40,40)){
	  res= true;
	  end=true;
	}
	if (in_rectangle(event.button.x,event.button.y,190,135,40,40)){
	  res= false;
	  end=true;
	}
	break;
      default:
	break;
      }
    }
  }
  SDL_RenderPresent(renderer);
  SDL_FreeSurface(sprite);
  SDL_DestroyTexture(texture);
  SDL_DestroyWindow(screen);
  return res;
}

game create_valid_game(int nb_pieces, int* best_play){
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
  sprite = IMG_Load("../../rushHour/Images/loading.bmp");
  SDL_Texture *texture= SDL_CreateTextureFromSurface(renderer,sprite);
  SDL_Rect pos= {0, 0, 400, 200};
  SDL_RenderCopy(renderer, texture, NULL, &pos);
  SDL_RenderPresent(renderer);
  bool end=false;
  game g;
  while (!end){
    piece* grille = array_pieces(nb_pieces); 
    game tmp = new_game_hr(nb_pieces,grille);
    *best_play=is_valid_game(tmp);
    if ( *best_play > 5){
      end=true;
      g=tmp;
    }
    else delete_game(tmp);
  }
  SDL_RenderPresent(renderer);
  SDL_FreeSurface(sprite);
  SDL_DestroyTexture(texture);
  SDL_DestroyWindow(screen);
  return g; 
}

int make_choice(bool is_random){
  SDL_Window *screen = SDL_CreateWindow("Choix", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 400, 200, SDL_WINDOW_SHOWN);
  if(screen == NULL){
    erreur_window();
    SDL_Quit();
    return EXIT_FAILURE;
  }
  SDL_Renderer *renderer = SDL_CreateRenderer(screen,-1, SDL_RENDERER_ACCELERATED|SDL_RENDERER_TARGETTEXTURE);
  if (renderer == NULL){
    erreur_renderer();
  }
  SDL_Surface *sprite ;
  if(is_random) sprite = IMG_Load("../../rushHour/Images/nbpieces.bmp");
  else sprite = IMG_Load("../../rushHour/Images/selectLvl.bmp");
  SDL_Texture *texture= SDL_CreateTextureFromSurface(renderer,sprite);
  SDL_Rect pos= {0, 0, 400, 200};
  SDL_RenderCopy(renderer, texture, NULL, &pos);
  SDL_RenderPresent(renderer);
  SDL_Event event;
  bool stop=false;
  int taille_case=50;
  int y_case=120;
  int res=0;
  while(!stop){
    while (SDL_PollEvent(&event)){
      switch (event.type){
      case SDL_MOUSEBUTTONUP:
	for (int i=taille_case, cpt=1; i<350; i+=50, cpt++){
	  if( in_rectangle(event.button.x,event.button.y,i,y_case,taille_case,taille_case)){
	    if(is_random) res= cpt+5;
	    else res=cpt;
	    stop = true;
	  }
	}
	break;
      default:
	break;
      }
    }
  }
  SDL_FreeSurface(sprite);
  SDL_DestroyTexture(texture);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(screen);
  return res;
}

bool make_move(SDL_Renderer *renderer, game g, int best_play){
  SDL_Event event, event2;
  bool end = false;
  int moving_piece;
  while (!end){
    while (SDL_PollEvent(&event)){
      switch (event.type){
      case SDL_MOUSEBUTTONUP:
	if(in_rectangle(event.button.x,event.button.y,100,100,600,600)){
	  //l'utilisateur a cliqué sur la grille
	  moving_piece=graphic_position_to_piece((cgame)g,event.button.x,event.button.y);
	  if(moving_piece>-1){
	    game_display(renderer,(cgame)g, best_play, moving_piece);
	    //l'utilisateur a cliqué sur une pièce
	    while(SDL_WaitEvent(&event2)){
	      switch(event2.type){
	      case SDL_MOUSEBUTTONUP:
		if(in_rectangle(event2.button.x,event2.button.y,100,100,600,600)){
		  //l'utilisateur a cliqué sur la grille
		  if(move_piece_SDL(g, moving_piece, event2.button.x, event2.button.y)){
		    return true;
		  }
		  if(graphic_position_to_piece((cgame)g,event2.button.x,event2.button.y)==moving_piece){
		    game_display(renderer,(cgame)g, best_play, -1);
		    return true;
		  }
		}
		break;
	      case SDL_QUIT:
		return false;
	      default:
		break;
	      }
	    }
	  }
	}
	break;
      case SDL_QUIT:
	return false;
      default:
	break;
      }
    }
  }
}


   
bool move_piece_SDL(game g, int indP, int x, int y){
  int X = (x-100)/100;
  int Y = 5-((y-100)/100);
  dir D;
  int dist = 0;
  cpiece p = game_piece((cgame) g, indP); 
  if(is_horizontal(p)){
    if(Y != get_y(p)){
      return false;
    }else{
      if(X == get_x(p)){
	return false;
      }else if(X > get_x(p)){
	D = RIGHT;
	dist = X-get_x(p);
      }else{
	D = LEFT;
	dist = get_x(p)-X;
      }
    }
  }
  else{
    if(X != get_x(p)){
      return false;
    }else{
      if(Y == get_y(p)){
	return false;
      }else if(Y > get_y(p)){
	D = UP;
	dist = Y-get_y(p);
      }else{
	D = DOWN;
	dist = get_y(p)-Y;
      }
    }
  }
  return play_move(g, indP, D, dist);
}
