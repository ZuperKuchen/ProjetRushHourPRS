#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <piece.h>
#include <game.h>
#include "graph.h"
#include "displayRH.h"
#include "displayAR.h"

void display_graph(graph G,bool isRH){
  node current_node;
  for(int i = 0; i < graph_get_nbNodes(G); i++){
    current_node = graph_get_node(G, i);
    printf("Node %d voisin de :\n", i);
    for(int j = 0; j < node_get_nbLinked(current_node); j++){
      printf("_%d", node_get_linked(current_node, j));
    }
    printf("\n");
    if(isRH) displayRH((cgame)node_get_game(current_node));
    else displayAR((cgame)node_get_game(current_node));
  }
}
	  
  
