#include <ctime>
#include <iostream>

#include "Grid.h"
#include "MovementBoard.h"
#include "Settings.h"
#include "Tetromino.h"
#include <FEHLCD.h>

int tetrisBoardWidth = 10;
int tetrisBoardHeight = 20;

int keyDebounce = 200;

// initialize MovementBoard with a coordinate (top left corner)
MovementBoard::MovementBoard(int Inx, int Iny, PlayerSettings &playerSettings)
    : grid(tetrisBoardWidth, tetrisBoardHeight), input(playerSettings) {
    // these are where the board is built around in world coords (top left corner)
    xMax = xMin + (tetrisBoardWidth - 1) * SCALE;
    yMax = yMin + (tetrisBoardHeight)*SCALE;

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
        std::cout << "GRAVITY!\n";
    } else {
        minoGravity = false;
    }

    // keyboard inputs
    input.update();

    if (input.keyLeft.newPress() && isBetween(movingX - 1, xMin, xMax)) {
        // grid.removeMino(convertToGridCoordsX(movingX), convertToGridCoordsY(movingY));
        movingX -= SCALE;
    }
    if (input.keyRight.newPress() && isBetween(movingX + 1, xMin, xMax)) {
        // grid.removeMino(convertToGridCoordsX(movingX), convertToGridCoordsY(movingY));
        movingX += SCALE;
    }
    // if ((keyU.onClick() || keyU.onDebounceEnd()) && isBetween(movingY + 1, yMin, yMax)) {
    //     // grid.removeMino(convertToGridCoordsX(movingX), convertToGridCoordsY(movingY));
    //     movingY += SCALE;
    // }
    // down triggers if minogravity needs to tick
    if (input.softDrop.pressed() && isBetween(movingY - 1, yMin, yMax)) {
        // grid.removeMino(convertToGridCoordsX(movingX), convertToGridCoordsY(movingY));
        movingY -= SCALE;
    }

    // render mino
    if (isBetween(movingX, xMin, xMax) && isBetween(movingY, yMin, yMax)) {
        // grid.drawMino(convertToGridCoordsX(movingX), convertToGridCoordsY(movingY), BLUE);
        grid.addMino(movingType, convertToGridCoordsX(movingX), convertToGridCoordsY(movingY));
        draw();

        // std::cout << convertToGridCoordsY(movingY);
    }

    // std::cout << "Move X: " << movingX << ", Grid X: " << convertToGridCoordsX(movingX) << std::endl;
    // std::cout << "Move Y: " << movingY << ", Grid Y: " << convertToGridCoordsY(movingY) << std::endl;
    // std::cout << "movingX: " << movingX << ", XMax: " << (xMax) << std::endl;
    // std::cout << "movingY: " << movingY << ", YMax: " << (yMax) << std::endl;
    // LCD.DrawCircle(120,220,1);
    // LCD.DrawCircle(40,60,1);

    draw();
}

// transforms the MovementBoard coordinate grid (bottom left being 0,0) to grid coordinate system (world coordinate
// system 0,0 top left)
int MovementBoard::convertToGridCoordsX(int x) { return x + boardX; }
// transforms the MovementBoard coordinate grid (bottom left being 0,0) to grid coordinate system (world coordinate
// system 0,0 top left)
int MovementBoard::convertToGridCoordsY(int y) { return boardY + tetrisBoardHeight * SCALE - y - SCALE; }

// draws a tetromino with the bottom left corner at pos_x and pos_y on the MovementBoard coordinate grid
void MovementBoard::drawTetromino(int pos_x, int pos_y, Tetromino type, TetrominoOrientation orientation) {}

// draws a moving tetromino starting with the bottom left corner at pos_x and pos_y on the MovementBoard coordinate grid
void MovementBoard::setMovingTetromino(int pos_x, int pos_y, Tetromino type, TetrominoOrientation orientation) {
    movingX = pos_x;
    movingY = pos_y;
    movingType = type;
    movingOrientation = orientation;
}
