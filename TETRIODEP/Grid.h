#pragma once

#include "../TETRIODEP/Tetromino.h"
#include <vector>
#include <FEHLCD.h>

class Grid {
  private:
  public:
    // scale of minos
#define SCALE 8 // was 6
    std::vector<Tetromino> data;
    int width;
    int height;

    int backgroundColor = BLACK;

    Grid(int width, int height);

    //adds mino with random color to the grid
    void addMino(Tetromino mino, int x, int y);
    void draw(int pos_x, int pos_y);
    // void drawBoarder(int pos_x, int pos_y);

    void minoShading(int pos_x, int pos_y, int color);

    void drawMino(int pos_x, int pos_y, int color);
    void removeMino(int pos_x, int pos_y);
};
