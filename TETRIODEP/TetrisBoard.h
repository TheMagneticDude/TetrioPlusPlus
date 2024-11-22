#pragma once

#include "Grid.h"
#include "Input.h"
#include "Tetromino.h"

class TetrisBoard {
  private:
    Grid grid;
    Grid fallingGrid;
    // tetrominos, all centered around bottom left

    PlayerInput input;

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
    // These are global screen coordinates
    int boardX;
    int boardY;
    // These are grid coordinates
    int fallingX;
    int fallingY;

    TetrisBoard(int x, int y, PlayerSettings &playerSettings);
    void update();
    // Returns true if a collision was detected
    bool checkCollision(Grid with, int x, int y);
    Grid createGrid(Tetromino type, TetrominoOrientation orientation);

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
