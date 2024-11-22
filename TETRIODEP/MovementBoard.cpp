#include <ctime>
#include <iostream>

#include "Grid.h"
#include "MovementBoard.h"
#include "Settings.h"
#include "Tetromino.h"
#include <FEHLCD.h>

int tetrisBoardWidth = 10;
int tetrisBoardHeight = 20;

// initialize MovementBoard with a coordinate (top left corner)
MovementBoard::MovementBoard(int Inx, int Iny, PlayerSettings &playerSettings)
    : grid(tetrisBoardWidth, tetrisBoardHeight), input(playerSettings) {
    // these are where the board is built around in world coords (top left corner)
    xMax = xMin + (tetrisBoardWidth - 1);
    yMax = yMin + (tetrisBoardHeight);

    boardX = Inx;
    boardY = Iny;
}

bool MovementBoard::isBetween(int n, int min, int max) { return n >= min && n <= max; }
bool MovementBoard::isTimeUp(time_t now, time_t &target, float tick) {
    if (target < now) {
        target = now + tick;
        return true;
    }
    return false;
}

// draws the entire MovementBoard
void MovementBoard::draw() { grid.draw(boardX, boardY); }

// updates the MovementBoard piece given keyboard inputs
void MovementBoard::update() {
    // mino gravity
    bool minoGravity = false;

    time_t now = time(NULL);

    if (isTimeUp(now, nextGravityTick, minoGravityTick)) {
        minoGravity = true;
    } else {
        minoGravity = false;
    }

    // keyboard inputs
    input.update();

    if (input.keyLeft.newPress() && isBetween(movingX - 1, xMin, xMax)) {
        movingX --;
    }
    if (input.keyRight.newPress() && isBetween(movingX + 1, xMin, xMax)) {
        movingX ++;
    }
    
    if (input.softDrop.pressed() && isBetween(movingY + 1, yMin, yMax)) {
        movingY ++;
    }

    // render mino
    if (isBetween(movingX, xMin, xMax) && isBetween(movingY, yMin, yMax)) {
        grid.addMino(movingType, (movingX), (movingY));
        draw();
            }


    draw();
}

// draws a tetromino with the bottom left corner at pos_x and pos_y on the MovementBoard coordinate grid
void MovementBoard::drawTetromino(int pos_x, int pos_y, Tetromino type, TetrominoOrientation orientation) {}

// draws a moving tetromino starting with the bottom left corner at pos_x and pos_y on the MovementBoard coordinate grid
void MovementBoard::setMovingTetromino(int pos_x, int pos_y, Tetromino type, TetrominoOrientation orientation) {
    movingX = pos_x;
    movingY = pos_y;
    movingType = type;
    movingOrientation = orientation;
}
