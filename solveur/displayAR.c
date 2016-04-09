#include <stdlib.h>
#include <stdio.h>
#include "displayAR.h"
#include <game.h>
#include <piece.h>
#define EMPTY_CASE_VALUE -1
#define WIDTH 4
#define HEIGHT 5

void cases_displayAR(cgame g,int nb,int tab_game[WIDTH][HEIGHT]){     
  for(int yt=HEIGHT-1; yt>=0; yt--){
    printf("%d ",yt);
    for(int xt=0; xt<WIDTH; xt++){
      if(tab_game[xt][yt]==EMPTY_CASE_VALUE){
	printf("[ ");
      }
      else{
	printf("[%d", tab_game[xt][yt]);
      }
      printf("]");
    }
    printf("\n");
  }
  printf(" \n");
  printf("   0");
  for(int k=1;k<WIDTH;k++) printf("  %d",k);
  printf("\n\n");
}

void init_displayAR(cgame g,int nb,int tab_game[WIDTH][HEIGHT]){     
  for(int i=0; i<WIDTH; i++){
    for(int j=0; j<HEIGHT; j++) tab_game[i][j]=EMPTY_CASE_VALUE ;
  }
  for(int i=0;i<nb;i++){
    cpiece tmp_piece = game_piece(g,i);
    int x = get_x(tmp_piece);
    int y = get_y(tmp_piece);
    for(int j=0; j<get_height(tmp_piece); j++){
      for(int k=0;k<get_width(tmp_piece);k++) tab_game[x+k][y+j] = i;
    }
  }
}

void displayAR(cgame g){
  printf("\n");
  int nb = game_nb_pieces(g);
  int tab_game[WIDTH][HEIGHT];
  init_displayAR(g,nb,tab_game);
  cases_displayAR(g,nb,tab_game);
}
