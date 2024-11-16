#ifndef TETRISBOARD.H
#define TETRISBOARD .H

#include "../TETRIODEP/Grid.h"
class TetrisBoard {
  private:
    Grid grid;

  public:
    TetrisBoard();
    void draw(int pos_x, int pos_y);
};
#endif