#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "test_game.h"
#include "game.h"
#include "piece.h"

bool test_game_nb_piece(game testg, int expectedVal){
  return game_nb_pieces((cgame)testg) == expectedVal;
}

bool test_game_piece(game testg, int num_piece, int expectedX, int expectedY){
  cpiece pieces = game_piece((cgame)testg, num_piece);
  return (get_x((piece)pieces) == expectedX) && (get_y((piece)pieces) == expectedY);
}

bool test_copy_game(game testg){
  game newGame = (game)malloc(sizeof(game));
  copy_game(testg,newGame);
  if((newGame->mov)== (testg->mov)){
    if((newGame->nb_pieces)==(testg->nb_pieces)){
      return true;
    }
  }
  return false;
}

bool test_play_move(game testg,dir d){
  bool ok= play_move(testg,0,d,4);
  return ok && game_over_hr((cgame)testg);
}

int main(int argc, char *argv[]){
  piece* tab_pieces=(piece*)malloc(sizeof(piece));;
  dir di=RIGHT;
  tab_pieces[0]=new_piece_rh(0,3,true,true);
  tab_pieces[1]=new_piece_rh(1,2,false,true);
  tab_pieces[2]=new_piece_rh(4,0,false,false);
  game testg = new_game_hr(3,tab_pieces);
  bool result = true;
  result = result && test_game_nb_piece(testg, 3);
  result = result && test_game_piece(testg, 2, 4, 0);
  //result = result && test_copy_game(testg);
  result = result && !(is_out(tab_pieces[0]));
  result = result && test_play_move(testg,di);
  if(result) printf("youpi test_game\n");
}
  
