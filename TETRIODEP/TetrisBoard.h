#pragma once

#include <optional>
#include <random>

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
    int shadowY;

    float gravityRate = 0.7;
    std::chrono::high_resolution_clock::time_point lastGravity;
    std::chrono::high_resolution_clock::time_point timeStart;
    float elapsedTime;
    std::string timeDisplay;

    bool onGround = false;
    std::chrono::high_resolution_clock::time_point startedOnGround;

    std::optional<Tetromino> hold;
    bool didHold = false;

    std::mt19937 randomGen;
    std::vector<Tetromino> queue;
    std::vector<Tetromino> bag;

    int linesCleared;
    int pendingGarbage = 0;
    TetrisBoard *opponent;

    float fourtyLineTime;

    bool ended;

    void updateRotation();
    // Returns true if a collision was detected
    bool checkCollision(Grid with, int x, int y);
    Grid createGrid(Tetromino type, TetrominoOrientation orientation);
    void settleGrid(Grid from, int fromX, int fromY);
    void startNewFalling(std::optional<Tetromino> mino = {});
    void clearLine(int y);
    void receiveLines(int numLines);
    void attackOpponent(int numLines);
    Tetromino getNextFromQueue();
    Tetromino getNextFromBag();
    void drawBorder();
    void drawStats();

  public:
    TetrisBoard(int x, int y, PlayerSettings &playerSettings, Statistics &playerStats, TetrisBoard *opponent,
                int randomSeed);
    void update();
    void draw();
    bool gameEnded();
    bool fourtyLinesEnded();
    int getLinesCleared();

    float getFourtyLinesClearedTime();

    static void *playSound(void *vargp);
};
