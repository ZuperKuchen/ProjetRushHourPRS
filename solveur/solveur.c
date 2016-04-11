#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <game.h>
#include <piece.h>
#include "displayRH.h"
#include "displayAR.h"
#include "graphe.h"

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

piece* read_Config_txtRH(int *width,int *height,int *nbPieces){
  FILE *file = fopen("../../solveur/rushHour.txt","r");
  if(file==NULL){
    printf("not file \n");
    return false;
  }
  grid_size(file,width,height);
  grid_nbPieces(file,nbPieces);
  piece* tableau = (piece*)malloc((*nbPieces) * sizeof(piece));
  create_grid(file,*nbPieces,tableau);
  fclose(file);
  return tableau;
}

piece* read_Config_txtAR(int *width,int *height,int *nbPieces){
  FILE *file = fopen("../../solveur/aneRouge.txt","r");
  if(file==NULL){
    printf("not file \n");
    return false;
  }
  grid_size(file,width,height);
  grid_nbPieces(file,nbPieces);
  piece* tableau = (piece*)malloc((*nbPieces) * sizeof(piece));
  create_grid(file,*nbPieces,tableau);
  fclose(file);
  return tableau;
}
 
int main(int argc,char* argv[]){
  int width = 0;
  int height = 0;
  int nbPieces = 0;
  char choose_game[3];
  bool good = false;
  while(!good){
    printf("\n Choisissez :\n   -0 pour rushhour\n   -1 pour anerouge\n");
    fgets(choose_game,3,stdin);
    int number_of_game = atoi(choose_game);  
    if(number_of_game == 0){
      piece *grid = read_Config_txtRH(&width,&height,&nbPieces);
      game rushHour = new_game_hr(nbPieces,grid);
      displayRH((cgame)rushHour);
      delete_game(rushHour);
      good = true;
    }
    else if(number_of_game==1){
      piece *grid = read_Config_txtAR(&width,&height,&nbPieces);
      game aneRouge = new_game(width,height,nbPieces,grid);
      displayAR((cgame)aneRouge);
      delete_game(aneRouge);
      good = true;
    }
    else return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
  

  
