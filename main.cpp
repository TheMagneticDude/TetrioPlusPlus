#include <FEHLCD.h>
#include <FEHRandom.h>
#include <cstdint>
#include <optional>
#include <vector>

#include "../TETRIODEP/Grid.h"
#include "../TETRIODEP/Menu.h"
#include "../TETRIODEP/TetrisBoard.h"
#include "../TETRIODEP/Tetromino.h"

// for key and mouse input
#include <Windows.h>

int main() {
    int board1Loc[2] = {40, 60};
    int board2Loc[2] = {200, 60};
    TetrisBoard board1(board1Loc[0], board1Loc[1]);
    TetrisBoard board2(board2Loc[0], board2Loc[1]);

    Menu mainMenu = Menu();

    while (1) {

        // Button s = Button(0,0,70,20,"BUTTON");
        // s.updateButtonState();

        if (mainMenu.start.getButtonTriggered()) {
            // clear main menu screen
            if (mainMenu.start.onButtonClicked()) {
                LCD.Clear();
            }

            mainMenu.remove();
            
            board1.draw();
            board2.draw();

            board1.drawTetromino(0, 0, static_cast<Tetromino>(2), TetrominoOrientation::H);

            board1.drawBorder();
            board2.drawBorder();
            board1.drawRandom();
            board2.drawRandom();

        } else if (mainMenu.start.onButtonReleased()) {
            LCD.Clear();
        }else{
            mainMenu.update();
        }

        

        // board1.drawMino(0,0);

        LCD.Update();

        // debug mouse pointer
        LPPOINT point;
        GetCursorPos(point);
    }

    return 0;
}
