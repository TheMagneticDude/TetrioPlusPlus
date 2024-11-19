#include <FEHLCD.h>
#include <FEHRandom.h>
#include <cstdint>
#include <optional>
#include <vector>
#include <Tetromino.h>

#include "../TETRIODEP/Grid.h"
#include "../TETRIODEP/TetrisBoard.h"
#include "../TETRIODEP/Tetromino.h"

// for key and mouse input
#include <Windows.h>

int main() {
    int board1Loc[2] = {40, 60};
    int board2Loc[2] = {200, 60};
    TetrisBoard board1(board1Loc[0], board1Loc[1]);
    TetrisBoard board2(board2Loc[0], board2Loc[1]);

    while (1) {
        LCD.Clear();

        board1.draw();
        board2.draw();

        board1.drawTetromino(0,0,static_cast<Tetromino>(2), TetrominoOrientation::H);


        // board1.drawRandom();
        // board2.drawRandom();
        board1.drawBoarder();
        board2.drawBoarder();

        // board1.drawMino(0,0);

        LCD.Update();

        // debug mouse pointer
        LPPOINT point;
        GetCursorPos(point);
    }

    return 0;
}
