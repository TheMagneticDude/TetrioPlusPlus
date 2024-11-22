#pragma once

#include <ctime>

#include "Grid.h"
#include "Input.h"
#include "Settings.h"

class MovementBoard {
  private:
    Grid grid;

    PlayerInput input;

    // bounderies to confine the mino
    int xMin = 0; // tetris board coords
    int yMin = 0;

    int xMax;
    int yMax;

    // current moving piece's info
    int movingX;
    int movingY;
    Tetromino movingType;
    TetrominoOrientation movingOrientation;

    // moving piece timing vars

    // gravity tick in seconds
    float minoGravityTick = 1;
    time_t nextGravityTick;

    void updateInput();

  public:
    int boardX;
    int boardY;
    MovementBoard(int x, int y, PlayerSettings &playerSettings);
    bool isTimeUp(time_t now, time_t &target, float tick);
    bool isBetween(int n, int min, int max);
    void draw();
    void update();
    void drawTetromino(int pos_x, int pos_y, Tetromino type, TetrominoOrientation orientation);
    int convertToGridCoordsX(int x);
    int convertToGridCoordsY(int y);

    void setMovingTetromino(int pos_x, int pos_y, Tetromino type, TetrominoOrientation orientation);

};
