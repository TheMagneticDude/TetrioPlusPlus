#include "../TETRIODEP/MovementBoard.h"
#include "../TETRIODEP/Grid.h"
#include "../TETRIODEP/TetrisBoard.h"
#include "../TETRIODEP/Tetromino.h"
#include "FEHRandom.h"
#include <FEHLCD.h>
#include <iostream>

// initialize MovementBoard with a coordinate (top left corner)
MovementBoard::MovementBoard(int Inx, int Iny) : grid(10, 20) {
    // these are where the board is built around in world coords (top left corner)
    keyL = false;
    keyR = false;

    MovementBoard::boardX = Inx;
    MovementBoard::boardY = Iny;
}

// draws the entire MovementBoard
void MovementBoard::draw() { grid.draw(boardX, boardY); }

// updates the MovementBoard piece given keyboard inputs
void MovementBoard::update(bool L, bool R) {
    keyL = L;
    keyR = R;

    if(keyL){
        movingX--;
    }
    if(keyR){
        movingX++;
    }

    draw();
}

// transforms the MovementBoard coordinate grid (bottom left being 0,0) to grid coordinate system (world coordinate
// system 0,0 top left)
int MovementBoard::convertToGridCoordsX(int x) { return x + boardX; }
// transforms the MovementBoard coordinate grid (bottom left being 0,0) to grid coordinate system (world coordinate
// system 0,0 top left)
int MovementBoard::convertToGridCoordsY(int y) { return boardY + 20 * SCALE - y * SCALE; }

// draws a tetromino with the bottom left corner at pos_x and pos_y on the MovementBoard coordinate grid
void MovementBoard::drawTetromino(int pos_x, int pos_y, Tetromino type, TetrominoOrientation orientation) {}

// draws a moving tetromino starting with the bottom left corner at pos_x and pos_y on the MovementBoard coordinate grid
void MovementBoard::drawMovingTetromino(int pos_x, int pos_y, Tetromino type, TetrominoOrientation orientation) {

    grid.drawMino(20, 100, BLUE);
}