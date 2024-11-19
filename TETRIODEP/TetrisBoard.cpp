#include "../TETRIODEP/TetrisBoard.h"
#include "../TETRIODEP/Grid.h"
#include "../TETRIODEP/Tetromino.h"
#include "FEHRandom.h"

//initialize tetrisboard with a coordinate (top left corner)
TetrisBoard::TetrisBoard(int Inx, int Iny) : grid(10, 20) {
    //these are where the board is built around in world coords (top left corner)
    TetrisBoard::boardX = Inx;
    TetrisBoard::boardY = Iny;
}

//draws the entire tetrisboard
void TetrisBoard::draw() { 
     grid.draw(boardX, boardY);
    }
    //draws random minos across tetris board
    void TetrisBoard::drawRandom(){
        for (int x = 0; x < 10; x++) {
        for (int y = 0; y < 20; y++) {
            // was for generating random minos
            auto mino = static_cast<Tetromino>(Random.RandInt() % 7);
            grid.data[y * 10 + x] = mino;
        }
    }
    }
// draws boarder around board
void TetrisBoard::drawBoarder() { grid.drawBoarder(boardX, boardY); }
//transforms the tetris board coordinate grid (bottom left being 0,0) to grid coordinate system (world coordinate system 0,0 top left)
int TetrisBoard::convertToGridCoordsX(int x){
    return x + boardX;
}
//transforms the tetris board coordinate grid (bottom left being 0,0) to grid coordinate system (world coordinate system 0,0 top left)
int TetrisBoard::convertToGridCoordsY(int y){
    return boardY + 20*6 - y*6;
}
// draws a tetromino with the bottom left corner at pos_x and pos_y on the tetris board coordinate grid
void TetrisBoard::drawMino(int pos_x, int pos_y, Tetromino type) {
    //create mino
     auto mino = static_cast<Tetromino>(type);
    }