#pragma once

#include <optional>

#include "Grid.h"
#include "Input.h"
#include "Settings.h"
#include "Tetromino.h"

class TetrisBoard {
  private:
    // These are global screen coordinates
    int boardX;
    int boardY;

    Grid grid;
    Grid fallingGrid;
    Grid holdGrid;
    std::vector<Grid> queueGrids;

    Tetromino fallingMino;
    TetrominoOrientation fallingRotation;

    PlayerInput input;
    PlayerSettings *settings;

    // These are grid coordinates
    int fallingX;
    int fallingY;

    float gravityRate = 0.7;
    std::chrono::high_resolution_clock::time_point lastGravity;

    std::optional<Tetromino> hold;
    bool didHold = false;

    std::vector<Tetromino> queue;
    std::vector<Tetromino> bag;

    bool ended;

    void updateRotation();
    // Returns true if a collision was detected
    bool checkCollision(Grid with, int x, int y);
    Grid createGrid(Tetromino type, TetrominoOrientation orientation);
    void settleGrid(Grid from, int fromX, int fromY);
    void startNewFalling(std::optional<Tetromino> mino = {});
    void clearLine(int y);
    Tetromino getNextFromQueue();
    Tetromino getNextFromBag();
    void drawBorder();


  public:
    TetrisBoard(int x, int y, PlayerSettings &playerSettings);
    void update();
    void draw();
    bool gameEnded();
};
