#ifndef GRID_H
#define GRID_H
#include "../TETRIODEP/Tetromino.h"
#include <vector>

class Grid {
  private:
    int width;
    int height;

  public:
// scale of minos
#define SCALE 8 // was 6
    std::vector<Tetromino> data;

    Grid(int width, int height);

    void addMino(Tetromino mino);
    void draw(int pos_x, int pos_y);
    void drawBoarder(int pos_x, int pos_y);

    void minoShading(int pos_x, int pos_y, int color);

    void drawMino(int pos_x, int pos_y, int color);
};

#endif
