#ifndef TETRISBOARD.H
#define TETRISBOARD .H
#include <Grid.h>
class TetrisBoard {
  private:
    Grid grid;

  public:
    TetrisBoard() : grid(10, 20) {}
    void draw(int pos_x, int pos_y) {}
};
#endif