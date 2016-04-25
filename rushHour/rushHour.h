#ifndef RUSHHOUR
#define RUSHHOUR

#include "game.h"
#include "piece.h"
#define GAME_SIZE 6
#define SMALL_SIZE 2
#define BIG_SIZE 3
#define EMPTY_CASE_VALUE -1
#define PIECE_MAX 9

int random(int max);

void possible_cases(bool small,bool horizontal,int *x,int *y);

bool random_bool(void);

bool test_unsolvable(piece p1,piece p2);

piece* array_pieces(int nombrePiece);

void display_init(cgame g,int nb,int tab_game[GAME_SIZE][GAME_SIZE]);

void display_cases(cgame g,int nb,int tab_game[GAME_SIZE][GAME_SIZE]);

void display(cgame g);

bool string_to_dir(dir *d,char *dir_str,bool vert);

bool want_to_quit(char *dir_str);

int choose_number_piece(int nbPiece, game g);

int choose_distance(game g);

bool choose_direction(game g,int num_piece,dir *direction);

void start_game(game g,int nbPiece);

bool play(int nbPieces);

void play_replay(bool replay,int nbPieces);

#endif
