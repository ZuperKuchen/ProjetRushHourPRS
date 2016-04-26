#ifndef CONFIG_SDL
#define CONFIG_SDL
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "config_sdl.h"
#include "game.h"
#include "piece.h"

game create_valid_game(int nb_pieces, int* best_play);
int choose_nb_pieces(void);
int is_valid_game(game g);
bool make_move(SDL_Renderer *renderer, game g, int best_play);
bool in_rectangle(int x,int y,int rectX, int rectY,int w,int h);
game init_config_text(int level);
bool play_graphic(SDL_Renderer *renderer,bool is_random);
int make_choice(bool is_random); 
bool move_piece_SDL(game g, int indP, int x, int y);
SDL_Surface* piece_to_sprite(cpiece p, int ind, bool select);
bool want_to_replay(void);
void piece_graphic_position(SDL_Rect *pos_piece, cpiece p);
int graphic_position_to_piece(cgame g,int x,int y);


#endif
