#pragma once

#include <optional>

#include "Grid.h"
#include "Input.h"
#include "Settings.h"
#include "Tetromino.h"

class TetrisBoard {
  private:
    Grid grid;
    Grid fallingGrid;
    Grid holdGrid;

    Tetromino fallingMino;

    PlayerInput input;
    PlayerSettings *settings;

    // These are grid coordinates
    int fallingX;
    int fallingY;

    float gravityRate = 0.7;
    std::chrono::high_resolution_clock::time_point lastGravity;

    std::optional<Tetromino> hold;
    bool didHold = false;

  public:
    // These are global screen coordinates
    int boardX;
    int boardY;

    TetrisBoard(int x, int y, PlayerSettings &playerSettings);
    void update();
    // Returns true if a collision was detected
    bool checkCollision(Grid with, int x, int y);
    Grid createGrid(Tetromino type, TetrominoOrientation orientation);
    void settleGrid(Grid from, int fromX, int fromY);
    void startNewFalling(std::optional<Tetromino> mino = {});

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
