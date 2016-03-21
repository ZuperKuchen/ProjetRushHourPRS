#ifndef TEST_GAME_H_
#define TEST_GAME_H_

struct piece_s {
  int x;
  int y;
  int width;
  int height;
  bool move_x;
  bool move_y;
};

typedef struct game_s* game;
typedef const struct game_s* cgame;
typedef struct piece_s* piece;
typedef const struct piece_s* cpiece;

struct game_s{
  int height;
  int width;
  int mov;
  int nb_pieces;
  piece pieces[];
};
bool is_out(piece p,game g);
#endif
