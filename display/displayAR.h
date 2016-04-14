#ifndef DISPLAYAR
#define DISPLAYAR

#define EMPTY_CASE_VALUE -1
#define WIDTH 4
#define HEIGHT 5

typedef struct game_s* game;
typedef const struct game_s* cgame;

void cases_displayAR(cgame g,int nb,int tab_game[WIDTH][HEIGHT]);
void init_displayAR(cgame g,int nb,int tab_game[WIDTH][HEIGHT]);
void displayAR(cgame g);

#endif
