#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <game.h>
#include <piece.h>
#define GAME_SIZE_RUSHHOUR 6
#define EMPTY_CASE_VALUE -1
#define WIDTH 4
#define HEIGHT 5

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
  printf("  ");
  printf("***      ***\n");
  printf(" ");
  for(int k=0;k<WIDTH;k++) printf("  %d",k);
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
  printf("Nombre de mouvements effectués : %d \n",game_nb_moves(g));
  printf("\n");
  int nb = game_nb_pieces(g);
  int tab_game[WIDTH][HEIGHT];
  init_displayAR(g,nb,tab_game);
  printf("  ************\n");
  cases_displayAR(g,nb,tab_game);
  printf("Pour quitter appuyez sur q \n");
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
  return tableau;
}
 
int main(int argc,char* argv[]){
  int width = 0;
  int height = 0;
  int nbPieces = 0;
  int jeu = atoi(argv[1]);
  if(jeu==0){
    piece *grid = read_Config_txtRH(&width,&height,&nbPieces);
    game rushHour = new_game_hr(nbPieces,grid);
    displayRH((cgame)rushHour);
  }
  else if(jeu==1){
    piece *grid = read_Config_txtAR(&width,&height,&nbPieces);
    game aneRouge = new_game(width,height,nbPieces,grid);
    displayAR((cgame)aneRouge);
  }
  else return EXIT_FAILURE;
  return EXIT_SUCCESS;
}
  

  
