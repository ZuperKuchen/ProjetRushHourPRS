#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <game.h>
#include "game_ar.h"
#include <piece.h>
#include "displayRH.h"
#include "displayAR.h"
#include "graph.h"
#include "displayGraph.h"

graph create_graph(game G, bool isRH);

static void usage(char *commande){
  fprintf(stderr," %s <a|r> <filename> \n",commande);
  exit(EXIT_FAILURE);
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
    if(line[4]==0) can_move_x = false;
    else can_move_x = true;
    if(line[5]==0) can_move_y = false;
    else can_move_y = true;
    tableau[i] = new_piece(line[0],line[1],line[2],line[3],can_move_x,can_move_y); 
  }
}

piece* read_Config_txt(FILE *file,int *width,int *height,int *nbPieces){
  if(file==NULL){
    printf("not file \n");
    exit(EXIT_FAILURE);
  }
  grid_size(file,width,height);
  grid_nbPieces(file,nbPieces);
  piece* tableau = (piece*)malloc((*nbPieces) * sizeof(piece));
  create_grid(file,*nbPieces,tableau);
  fclose(file);
  return tableau;
}


bool compare(char *c1[],char *c2){
  return strcmp(*c1,c2) == 0;
}

void display_solution(graph g,int number_solution,bool isRH){
  node solution_node = graph_get_node(g, number_solution);
  printf("Node %d voisin de :\n", number_solution);
  for(int j = 0; j < node_get_nbLinked(solution_node); j++){
    printf("_%d", node_get_linked(solution_node, j));
  }
  if(isRH) displayRH((cgame)node_get_game(solution_node));
  else displayAR((cgame)node_get_game(solution_node));
}

void config_rushHour(FILE* file,int *width,int *height,int *nbPieces){
  piece *grid = read_Config_txt(file,width,height,nbPieces);
  game rushHour = new_game_hr(*nbPieces,grid);
  displayRH((cgame)rushHour);
  graph solutions= create_graph(rushHour, true);
  display_solution(solutions,454,true);
  printf("Nombres de cases : %d\n", graph_get_nbNodes(solutions));
  printf("Derniere case solution : %d\n", game_over_hr(node_get_game(graph_get_node(solutions, graph_get_nbNodes(solutions)-1))));
  delete_game(rushHour);
}

void config_aneRouge(FILE* file,int *width,int *height,int *nbPieces){
  piece *grid = read_Config_txt(file,width,height,nbPieces);
  game aneRouge = new_game(*width,*height,*nbPieces,grid);
  displayAR((cgame)aneRouge);
  graph solutions= create_graph(aneRouge, false);
  display_solution(solutions,100,false);
  printf("Nombres de cases : %d\n", graph_get_nbNodes(solutions));
  printf("Derniere case solution : %d\n", game_over_ar(node_get_game(graph_get_node(solutions, graph_get_nbNodes(solutions)-1))));
  delete_game(aneRouge);
}

int main(int argc,char* argv[]){
  if(argc!=3) usage(argv[0]);
  int width = 0;
  int height = 0;
  int nbPieces = 0;
  FILE *file = fopen(argv[2],"r");
  char* choose_game[2];
  char *rh = "r";
  char *ar = "a";
  char *rush = "rushHour.txt";
  char *ane = "aneRouge.txt";
  choose_game[0] = argv[1];
  choose_game[1] = argv[2];
  if(compare(choose_game,rh) && compare(choose_game+1,rush)){
    config_rushHour(file,&width,&height,&nbPieces);
  }
  else if(compare(choose_game,ar) && compare(choose_game+1,ane)){
    config_aneRouge(file,&width,&height,&nbPieces);
  }
  else usage(argv[0]);
  return EXIT_SUCCESS;
}


  
graph create_graph(game G, bool isRH){
  bool end = false;
  int indNode = 0;
  node firstNode = new_empty_node(G);
  graph graph = new_graph(firstNode);
  int nbCases;
  int sol;
  
  while(!end){
    //display_graph(graph,isRH);
    game currentGame = copy_game_for_solver(node_get_game(graph_get_node(graph, indNode)));
    int nbPieces = game_nb_pieces((cgame)currentGame);
    game *tabGame = different_cases(currentGame, &nbCases);
    node father;
    for(int i=0; i<nbCases; i++){
      if(isRH && game_over_hr((cgame)tabGame[i])){
	sol = -2;
      }else if(!isRH && game_over_ar((cgame)tabGame[i])){
	sol = -2;
      }else{
	sol = already_exists(tabGame[i], graph);
      }
      if(sol == -1){
	int tab[0];
	tab[0] = indNode;
	graph = add_node_graph(graph, new_full_node(tabGame[i], tab ,1));
	put_new_adress(graph, add_linked(graph_get_node(graph, indNode), graph_get_nbNodes(graph)-1), indNode);
      }else if(sol == -2){
	int tab[0];
	tab[0] = indNode;
	graph = add_node_graph(graph, new_full_node(tabGame[i], tab ,1));
	put_new_adress(graph, add_linked(graph_get_node(graph, indNode), graph_get_nbNodes(graph)-1), indNode);
	end = true;
	break;
      }else{
	put_new_adress(graph, add_linked(graph_get_node(graph, sol), indNode), sol);
	put_new_adress(graph, add_linked(graph_get_node(graph, indNode), sol), indNode);
      }
    }
    free_cases(tabGame, nbCases);
    delete_game(currentGame);
    indNode ++;
  }
  //display_graph(graph,isRH);
  return graph;
}


	  
  

