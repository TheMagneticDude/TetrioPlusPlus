#include<TetrisBoard.h>
#include<Tetromino.h>
#include<Grid.h>
#include "FEHRandom.h"

    TetrisBoard::TetrisBoard() : grid(10, 20) {
        for (int x = 0; x < 10; x++) {
            for (int y = 0; y < 20; y++) {
                auto mino = static_cast<Tetromino>(Random.RandInt() % 7);
                grid.data[y * 10 + x] = mino;
            }
        }
    }

    void TetrisBoard::draw(int pos_x, int pos_y) { grid.draw(pos_x, pos_y); }