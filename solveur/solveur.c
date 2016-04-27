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
#include "solveur.h"


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
  printf("Position finale :\n");
  if(isRH) displayRH((cgame)node_get_game(solution_node));
  else displayAR((cgame)node_get_game(solution_node));
}

int config_rushHour(FILE* file,int *width,int *height,int *nbPieces){
  piece *grid = read_Config_txt(file,width,height,nbPieces);
  game rushHour = new_game(*width,*height,*nbPieces,grid);
  int solvable;
  graph solutions = create_graph(rushHour, true,&solvable);
  if(solvable == -1) return -1;
  solvable = simple_search(solutions);
  delete_game(rushHour);
  delete_graph(solutions);
  return solvable;
}

int config_aneRouge(FILE* file,int *width,int *height,int *nbPieces){
  piece *grid = read_Config_txt(file,width,height,nbPieces);
  game aneRouge = new_game(*width,*height,*nbPieces,grid);
  int solvable = 0;
  graph solutions = create_graph(aneRouge, false,&solvable);
  if(solvable == -1) return -1;
  solvable = simple_search(solutions);
  delete_game(aneRouge);
  delete_graph(solutions);
  return solvable;
}

  
graph create_graph(game G, bool isRH,int *solvable){
  bool end = false;
  int indNode = 0;
  node firstNode = new_empty_node(G);
  graph graph = new_graph(firstNode);
  int *nbCases = malloc(sizeof(int));
  int sol = 0;
  while(!end){
    if(indNode >= graph_get_nbNodes(graph)){
      *solvable = -1;
      return NULL;
    }
    game currentGame = copy_game_for_solver(node_get_game(graph_get_node(graph, indNode)));
    int nbPieces = game_nb_pieces((cgame)currentGame);
    game *tabGame = different_cases(currentGame, nbCases);
    node father;
    for(int i=0; i<*nbCases; i++){
      if(isRH && game_over_hr((cgame)tabGame[i])){
	sol = -2;
      }else if(!isRH && game_over_ar((cgame)tabGame[i])){
	sol = -2;
      }else{
	sol = already_exists(tabGame[i], graph);
      }
      if(sol == -1){
	int* tab = (int*)malloc(sizeof(int));
	*tab = indNode;
	graph = add_node_graph(graph, new_full_node(tabGame[i], tab ,1));
	put_new_adress(graph, add_linked(graph_get_node(graph, indNode), graph_get_nbNodes(graph)-1), indNode);
	free(tab);
      }else if(sol == -2){
	int* tab = (int*)malloc(sizeof(int));
	*tab = indNode;
	graph = add_node_graph(graph, new_full_node(tabGame[i], tab ,1));
	put_new_adress(graph, add_linked(graph_get_node(graph, indNode), graph_get_nbNodes(graph)-1), indNode);
	free(tab);
	end = true;
	break;
      }else{
	put_new_adress(graph, add_linked(graph_get_node(graph, sol), indNode), sol);
	put_new_adress(graph, add_linked(graph_get_node(graph, indNode), sol), indNode);
      }
    }
    free_cases(tabGame, *nbCases);
    delete_game(currentGame);
    indNode ++;
  }
  free(nbCases);
  return graph;
}

int simple_search(graph G){
  int currentNode = graph_get_nbNodes(G) - 1;
  int smallest = currentNode;
  int res = 0;
  while(currentNode > 0){
    for(int i=0; i<node_get_nbLinked(graph_get_node(G, currentNode)); i++){
      if(node_get_linked(graph_get_node(G, currentNode), i) < smallest){
	smallest = node_get_linked(graph_get_node(G, currentNode), i);
      }
    }
    currentNode = smallest;
    res++;
  }
  return res;
}
	  
  

