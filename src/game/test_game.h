#ifndef TEST_GAME_H_
#define TEST_GAME_H_

struct piece_s {
  int x;
  int y;
  bool small;
  bool horizontal;
};


typedef struct piece_s* piece;
typedef const struct piece_s* cpiece;

struct game_s{
  int mov;
  int nb_pieces;
  piece pieces[];
};
bool is_out(piece p);
#endif
