#include <stdio.h>
#include <stdlib.h>
#include <bool.h>
#include "game.h"
#include "piece.h"

bool test_game_nb_piece(game testg, int expectedVal){
  return game_nb_pieces((cgame)testg) == expectedVal;
}

bool test_game_piece(game testg, int num_piece, int expectedX, int expectedY){
  cpiece piece = game_piece((cgame)testg, num_piece);
  return get_x((piece)piece) == expectedX && get_y((piece)piece) == expectedY;
}

bool test_copy_game(game testg){
  

int main(int argc, char *argv[]){
  piece* tab_pieces;
  tab_pieces[0]=new_piece_rh(3,0,true,true);
  tab_pieces[1]=new_piece_rh(1,2,false,true);
  tab_pieces[2]=new_piece_rh(4,3,false,false);
  game testg = new_game_rh(3,tab_pieces);
  bool result = true;
  result = result && test_game_nb_piece(testg, 3);
  result = result && test_game_piece(testg, 2, 4, 3);
  
  result = result && test_copy_game(testg);
