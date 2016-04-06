#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <game.h>
#include <piece.h>
#define GAME_SIZE 6
#define EMPTY_CASE_VALUE -1

void display_init(cgame g,int nb,int tab_game[GAME_SIZE][GAME_SIZE]){
  for(int i=0; i<GAME_SIZE; i++){
    for(int j=0; j<GAME_SIZE; j++){
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

void display_cases(cgame g,int nb,int tab_game[GAME_SIZE][GAME_SIZE]){
  for(int yt=GAME_SIZE-1; yt>=0; yt--){
    printf("%d ",yt);
    for(int xt=0; xt<GAME_SIZE; xt++){
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
  for(int k=0;k<GAME_SIZE;k++) printf(" %d ",k);
  printf("\n\n");
}

void display(cgame g){
  printf("\n");
  int nb = game_nb_pieces(g);
  int tab_game[GAME_SIZE][GAME_SIZE];
  display_init(g,nb,tab_game);
  display_cases(g,nb,tab_game);
  printf("\n");
}

void grid_size(FILE *file,int *width,int *height){
  int line[5];
  fscanf(file,"%d %d",&line[0],&line[1]);
  *width = line[0];
  *height = line[1];
}

void grid_nbPieces(FILE *file,int *nbPieces){
  int line[3];
  fscanf(file,"%d",&line[0]);
  *nbPieces = line[0];
}

void create_grid(FILE *file,int nbPieces,piece *tableau){
  int line[20];
  for(int i=0; i<nbPieces; i++){
    bool can_move_x,can_move_y;
    fscanf(file,"%d %d %d %d %d %d",&line[0],&line[1],&line[2],&line[3],&line[4],&line[5]);
    if(line[4]==0) can_move_x == false;
    else can_move_x = true;
    if(line[5]==0) can_move_y == false;
    else can_move_y = true;
    tableau[i] = new_piece(line[0],line[1],line[2],line[3],can_move_x,can_move_y); 
  }
}

piece* read_Config_txt(int *width,int *height,int *nbPieces){
  FILE *file = fopen("../../rushHour/game.txt","r");
  if(file==NULL){
    printf("not file \n");
    return false;
  }
  grid_size(file,width,height);
  grid_nbPieces(file,nbPieces);
  piece* tableau = (piece*)malloc((*nbPieces) * sizeof(piece));
  create_grid(file,*nbPieces,tableau);
  return tableau;
}
 
int main(void){
  int width = 0;
  int height = 0;
  int nbPieces = 0;
  piece *grid = read_Config_txt(&width,&height,&nbPieces);
  game solveur = new_game_hr(nbPieces,grid);
  display((cgame)solveur);
  return EXIT_SUCCESS;
}
  

  
