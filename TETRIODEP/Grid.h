#pragma once

#include <vector>

#include "Tetromino.h"
#include <FEHLCD.h>

class Grid {
  private:
    void minoShading(int pos_x, int pos_y, int color);
    void drawMino(int pos_x, int pos_y, int color);

  public:
    // scale of minos
#define SCALE 8 // was 6
    std::vector<Tetromino> data;
    int width;
    int height;

    int backgroundColor = BLACK;

    Grid(int width, int height);

    Tetromino getAtPos(int x, int y);
    void addMino(Tetromino mino, int x, int y);
    void removeMino(int pos_x, int pos_y);

    void draw(int pos_x, int pos_y);
    // void drawBoarder(int pos_x, int pos_y);

};
