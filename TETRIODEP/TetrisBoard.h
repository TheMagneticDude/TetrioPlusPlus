#pragma once

#include "../TETRIODEP/Grid.h"
class TetrisBoard {
  private:
    Grid grid;
    Grid movement;
    // tetrominos, all centered around bottom left

    // line horizontal
    Grid Tetromno_I_H();
    // line verticle
    int Tetromno_I_V[4][4] = {
        {1, 0, 0, 0},
        {1, 0, 0, 0},
        {1, 0, 0, 0},
        {1, 0, 0, 0},
    };

    // square, only one rotation
    int Tetromno_O[4][4] = {
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {1, 1, 0, 0},
        {1, 1, 0, 0},
    };

    // t shaped piece upright
    int Tetromno_T_U[4][4] = {
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 1, 0, 0},
        {1, 1, 1, 0},
    };

    // t shaped piece turned right
    int Tetromno_T_R[4][4] = {
        {0, 0, 0, 0},
        {1, 0, 0, 0},
        {1, 1, 0, 0},
        {1, 0, 0, 0},
    };

    // t shaped piece turned upside down
    int Tetromno_T_D[4][4] = {
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 1, 0, 0},
        {1, 1, 1, 0},
    };

    // t shaped piece turned left
    int Tetromno_T_L[4][4] = {
        {0, 0, 0, 0},
        {0, 1, 0, 0},
        {1, 1, 0, 0},
        {0, 1, 0, 0},
    };

    // right snake upright
    int Tetromno_RS_U[4][4] = {
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 1, 1, 0},
        {1, 1, 0, 0},
    };

  public:
    int boardX;
    int boardY;
    TetrisBoard(int x, int y);
    void draw();
    void drawRandom();
    void drawBorder();
    int *getOrientation(int o);
    void drawTetromino(int pos_x, int pos_y, Tetromino type, TetrominoOrientation orientation);
    int convertToGridCoordsX(int x);
    int convertToGridCoordsY(int y);

    // movement methods
    void drawMovingTetromino(int pos_x, int pos_y, Tetromino type, TetrominoOrientation orientation);
};
