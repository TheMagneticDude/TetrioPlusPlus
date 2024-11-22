#include "TetrisBoard.h"
#include "FEHRandom.h"
#include "Grid.h"
#include "Tetromino.h"
#include <FEHLCD.h>

// initialize tetrisboard with a coordinate (top left corner)
TetrisBoard::TetrisBoard(int Inx, int Iny) : grid(10, 20), movement(10, 10) {
    // these are where the board is built around in world coords (top left corner)
    TetrisBoard::boardX = Inx;
    TetrisBoard::boardY = Iny;
}

// draws the entire tetrisboard
void TetrisBoard::draw() {
    grid.draw(boardX, boardY);
    movement.draw(boardX, boardY);
}
// draws random minos across tetris board
void TetrisBoard::drawRandom() {

    for (int x = 0; x < 10; x++) {
        for (int y = 0; y < 20; y++) {
            // was for generating random minos
            auto mino = static_cast<Tetromino>(Random.RandInt() % 7);

            grid.data[y * 10 + x] = mino;
        }
    }
}

// draws border around board excluding top
void TetrisBoard::drawBorder() {
    int borderScale = 4;
    // draws boarder around grid
    int pos_x = boardX;
    int pos_y = boardY;
    // bottom boarders
    LCD.SetFontColor(WHITE);

    // bottom boarder
    LCD.FillRectangle(pos_x - borderScale, pos_y + SCALE * (grid.height - 1), SCALE * (grid.width) + 2 * borderScale,
                      borderScale);

    // left and right boarders

    // Left boarder
    // LCD.FillRectangle(pos_x - SCALE, pos_y - SCALE*2, SCALE, SCALE * (grid.height + 2));
    LCD.FillRectangle(pos_x - borderScale, pos_y - borderScale * 2, borderScale, SCALE * (grid.height) + borderScale);
    // right boarder
    // LCD.FillRectangle(pos_x + SCALE * grid.width, pos_y - SCALE*2, SCALE, SCALE * (grid.height + 2));
    LCD.FillRectangle(pos_x - borderScale + SCALE * grid.width + borderScale, pos_y - borderScale * 2, borderScale,
                      SCALE * (grid.height) + borderScale);
}

// transforms the tetris board coordinate grid (bottom left being 0,0) to grid coordinate system (world coordinate
// system 0,0 top left)
int TetrisBoard::convertToGridCoordsX(int x) { return x + boardX; }
// transforms the tetris board coordinate grid (bottom left being 0,0) to grid coordinate system (world coordinate
// system 0,0 top left)
int TetrisBoard::convertToGridCoordsY(int y) { return boardY + 20 * SCALE - y * SCALE; }

// returns the correct tetromino array with orientation
int *getOrientation(Tetromino type, TetrominoOrientation o) {}

// draws a tetromino with the bottom left corner at pos_x and pos_y on the tetris board coordinate grid
void TetrisBoard::drawTetromino(int pos_x, int pos_y, Tetromino type, TetrominoOrientation orientation) {}

// draws a moving tetromino starting with the bottom left corner at pos_x and pos_y on the tetris board coordinate grid
void TetrisBoard::drawMovingTetromino(int pos_x, int pos_y, Tetromino type, TetrominoOrientation orientation) {
    movement.drawMino(20, 100, BLUE);
}