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

void pieces_graphic_position(SDL_Rect pos_pieces[], cgame g){
  int nb_pieces=game_nb_pieces(g);
  for (int i=0; i<nb_pieces; i++){
    cpiece p_aux=game_piece(g, i);
    pos_pieces[i].x=get_x(p_aux) * 100 + 100;
    pos_pieces[i].y=(- get_y(p_aux) + 6) * 100 + 100;
    pos_pieces[i].w=get_width(p_aux)*100;
    pos_pieces[i].h=get_height(p_aux)*100;
  }
}

bool cars_display(SDL_Renderer *renderer, cgame g){
  int nb_pieces=game_nb_pieces(g);
  SDL_Rect pos_pieces[nb_pieces];
  pieces_graphic_position(pos_pieces,g);
  SDL_Surface *sprites[nb_pieces];
  SDL_Texture *textures[nb_pieces];
  for (int i=0; i<nb_pieces ;i++){
    cpiece tmp= game_piece(g, i);
    if (i==0){
      sprites[0] = IMG_Load("../../rushHour/redCar.png");
      continue;
    }
    if (is_horizontal(tmp)){
      if(get_height(tmp)==3){
	sprites[i] = IMG_Load("../../rushHour/carRight3");
      }
      else{
	sprites[i] = IMG_Load("../../rushHour/carRight2");
      }
    }
    else if (get_width(tmp)==2){
      sprites[i] = IMG_Load("../../rushHour/carUp2");
    }
    else {
      sprites[i] = IMG_Load("../../rushHour/carUp3");
    }
    textures[i] = SDL_CreateTextureFromSurface(renderer,sprites[i]);
    SDL_RenderCopy(renderer, textures[i], NULL, &pos_pieces[i]);
    SDL_FreeSurface(sprites[i]);
    SDL_DestroyTexture(textures[i]);
    SDL_RenderPresent(renderer);
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
 
  SDL_Delay(4000);
  SDL_RenderClear(renderer);

  board_display(renderer);
  piece t_pieces[6]; //= malloc(6*sizeof(piece));
  FILE *niveau = fopen("../../rushHour/rushHour.txt","r");
  create_grid(niveau,6,t_pieces);
  game g= new_game (6,6,6,t_pieces);
  
  cars_display(renderer,(cgame)g);


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
