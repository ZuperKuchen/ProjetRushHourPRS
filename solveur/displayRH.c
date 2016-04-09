#include <stdlib.h>
#include <stdio.h>
#include "displayRH.h"
#include <game.h>
#include <piece.h>
#define GAME_SIZE_RUSHHOUR 6
#define EMPTY_CASE_VALUE -1

void display_initRH(cgame g,int nb,int tab_game[GAME_SIZE_RUSHHOUR][GAME_SIZE_RUSHHOUR]){
  for(int i=0; i<GAME_SIZE_RUSHHOUR; i++){
    for(int j=0; j<GAME_SIZE_RUSHHOUR; j++){
      tab_game[i][j]= EMPTY_CASE_VALUE;
    }
  }
  for(int i=0;i<nb;i++){
    cpiece tmp_piece = game_piece(g,i);
    int x = get_x(tmp_piece);
    int y = get_y(tmp_piece);
    if(is_horizontal(tmp_piece)){
      for(int j=0; j<get_width(tmp_piece); j++){
	tab_game[x+j][y] = i;
      }
    }else{
      for(int j=0; j<get_height(tmp_piece); j++){
	tab_game[x][y+j] = i;
      }
    }
  }
}

void display_casesRH(cgame g,int nb,int tab_game[GAME_SIZE_RUSHHOUR][GAME_SIZE_RUSHHOUR]){
  for(int yt=GAME_SIZE_RUSHHOUR-1; yt>=0; yt--){
    printf("%d ",yt);
    for(int xt=0; xt<GAME_SIZE_RUSHHOUR; xt++){
      if(tab_game[xt][yt]==EMPTY_CASE_VALUE){
	printf("[ ");
      }
      else{
	printf("[%d", tab_game[xt][yt]);
      }
      if(xt==5 && yt==3){
	printf("{");
      }else{
	printf("]");
      }
    }
    printf("\n");
  }
  printf("  ");
  for(int k=0;k<GAME_SIZE_RUSHHOUR;k++) printf(" %d ",k);
  printf("\n\n");
}


void displayRH(cgame g){
  printf("\n");
  int nb = game_nb_pieces(g);
  int tab_game[GAME_SIZE_RUSHHOUR][GAME_SIZE_RUSHHOUR];
  display_initRH(g,nb,tab_game);
  display_casesRH(g,nb,tab_game);
  printf("\n");
}
