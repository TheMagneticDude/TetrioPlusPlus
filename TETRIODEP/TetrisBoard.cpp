#include <iostream>

#include "TetrisBoard.h"
#include "FEHRandom.h"
#include "Grid.h"
#include "Input.h"
#include "Settings.h"
#include "Tetromino.h"
#include <FEHLCD.h>

// initialize tetrisboard with a coordinate (top left corner)
TetrisBoard::TetrisBoard(int _boardX, int _boardY, PlayerSettings &settings) : grid(10, 20), fallingGrid(3, 3), input(settings) {
    // these are where the board is built around in world coords (top left corner)
    boardX = _boardX;
    boardY = _boardY;
    // TODO:
    fallingX = 5;
    fallingY = 10;
    fallingGrid = createGrid(Tetromino::Z, TetrominoOrientation::H);
}

// draws the entire tetrisboard
void TetrisBoard::draw() {
    grid.draw(boardX, boardY);
    fallingGrid.draw(boardX + fallingX * SCALE, boardY - fallingY * SCALE);
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

void TetrisBoard::update() {
    input.update();

    bool pressedLeft = input.keyLeft.newPress();
    bool pressedRight = input.keyRight.newPress();
    if (pressedLeft && !pressedRight) {
        if (!checkCollision(fallingGrid, fallingX - 1, fallingY)) {
            fallingX--;
        }
    } else if (pressedRight && !pressedLeft) {
        if (!checkCollision(fallingGrid, fallingX + 1, fallingY)) {
            fallingX++;
        }
    }
}

bool TetrisBoard::checkCollision(Grid with, int withX, int withY) {
    for (int x = 0; x < with.width; x++) {
        for (int y = 0; y < with.height; y++) {
            Tetromino withMino = with.getAtPos(x, y);
            Tetromino gridMino;
            if (withX + x < 0 || withX + x >= 10) {
                gridMino = Tetromino::G;
            } else {
                gridMino = grid.getAtPos(withX + x, withY + y);
            }
            if (withMino != Tetromino::E && gridMino != Tetromino::E) {
                return true;
            }
        }
    }
    return false;
}

Grid TetrisBoard::createGrid(Tetromino type, TetrominoOrientation orientation) {
    int gridWidth = type == Tetromino::I ? 5 : 3;
    Grid newGrid(gridWidth, gridWidth);
    std::vector<int> newData;
    switch (type) {
    case Tetromino::I:
        newData = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        break;
    case Tetromino::J:
        newData = {2, 0, 0, 2, 2, 2, 0, 0, 0};
        break;
    case Tetromino::L:
        newData = {0, 0, 3, 3, 3, 3, 0, 0, 0};
        break;
    case Tetromino::O:
        newData = {0, 4, 4, 0, 4, 4, 0, 0, 0};
        break;
    case Tetromino::S:
        newData = {0, 5, 5, 5, 5, 0, 0, 0, 0};
        break;
    case Tetromino::T:
        newData = {0, 6, 0, 6, 6, 6, 0, 0, 0};
        break;
    case Tetromino::Z:
        newData = {7, 7, 0, 0, 7, 7, 0, 0, 0};
        break;
    default:
        std::cerr << "Tried to create grid with invalid tetromino type: " << static_cast<int>(type) << std::endl;
    }
    for (int i = 0; i < newData.size(); i++) {
        newGrid.data[i] = static_cast<Tetromino>(newData[i]);
    }
    return newGrid;
}