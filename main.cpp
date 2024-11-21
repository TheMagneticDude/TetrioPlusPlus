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

        // settings has not been implemented yet so disabled

        mainMenu.disable(mainMenu.settings);

        
        if (mainMenu.renderSubPage(mainMenu.start)) {
            LCD.SetFontColor(WHITE);
            LCD.WriteAt("\"Play\" Tetrio++ below!", 25, 20);
            mainMenu.remove();

            board1.draw();
            board2.draw();

            board1.drawTetromino(0, 0, static_cast<Tetromino>(2), TetrominoOrientation::H);

            board1.drawBorder();
            board2.drawBorder();
            board1.drawRandom();
            board2.drawRandom();
        }
        if (mainMenu.renderSubPage(mainMenu.stats)) {

            LCD.SetFontColor(WHITE);
            LCD.WriteAt("\"High\" score: 253", 0, 40);
            LCD.WriteAt("Best 40 line time: 3:42", 0, 70);
            LCD.WriteAt("Total Lines cleared: 512", 0, 100);
        }
        if (mainMenu.renderSubPage(mainMenu.credits)) {

            LCD.SetFontColor(WHITE);
            LCD.WriteAt("Tetrio++ Written by:", 0, 20);
            LCD.WriteAt("Nathan Cheng", 0, 50);
            LCD.WriteAt("Ojas Landge", 0, 90);
        }

        mainMenu.update();

        // board1.drawMino(0,0);

        LCD.Update();

        // debug mouse pointer
        LPPOINT point;
        GetCursorPos(point);
    }

    return 0;
}
