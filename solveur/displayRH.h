#ifndef DISPLAYRH
#define DISPLAYRH

#define GAME_SIZE_RUSHHOUR 6
#define EMPTY_CASE_VALUE -1

typedef struct game_s* game;
typedef const struct game_s* cgame;

void display_initRH(cgame g,int nb,int tab_game[GAME_SIZE_RUSHHOUR][GAME_SIZE_RUSHHOUR]);

void display_casesRH(cgame g,int nb,int tab_game[GAME_SIZE_RUSHHOUR][GAME_SIZE_RUSHHOUR]);

void displayRH(cgame g);

#endif
