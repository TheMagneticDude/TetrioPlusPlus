#include <FEHLCD.h>
#include <FEHRandom.h>
#include <cstdint>
#include <optional>
#include <vector>

#include "../TETRIODEP/Grid.h"
#include "../TETRIODEP/Menu.h"
#include "../TETRIODEP/MovementBoard.h"
#include "../TETRIODEP/Options.h"
#include "../TETRIODEP/TetrisBoard.h"
#include "../TETRIODEP/Tetromino.h"

int main() {
    Settings settings = defaultSettings;

    int board1Loc[2] = {40, 60};
    int board2Loc[2] = {200, 60};
    TetrisBoard board1(board1Loc[0], board1Loc[1]);
    MovementBoard movement1(board1Loc[0], board1Loc[1], settings.p2Settings);
    movement1.setMovingTetromino(0, 0, Tetromino::O, TetrominoOrientation::H);
    TetrisBoard board2(board2Loc[0], board2Loc[1]);
    MovementBoard movement2(board2Loc[0], board2Loc[1], settings.p1Settings);
    movement2.setMovingTetromino(0, 0, Tetromino::L, TetrominoOrientation::H);

    // Options page (set up for p1 for now ill create sliders and switches to change later)
    Options optionsPage = Options(settings.p1Settings);

    Menu mainMenu = Menu();

    while (1) {
        LCD.Clear();
        // Buttons  can set up button bindings etc later

        // settings has not been implemented yet so disabled

        // mainMenu.disable(mainMenu.settings);

        if (mainMenu.isPageActive(Menu::Option::Start)) {
            LCD.SetFontColor(WHITE);
            LCD.WriteAt("\"Play\" Tetrio++ below!", 25, 25);
            mainMenu.remove();

            board1.draw();
            board2.draw();

            board1.drawTetromino(0, 0, static_cast<Tetromino>(2), TetrominoOrientation::H);
            board1.drawBorder();
            board2.drawBorder();

            // update movement
            movement1.update();
        }
        if (mainMenu.isPageActive(Menu::Option::Settings)) {
            optionsPage.update();
        }

        if (mainMenu.isPageActive(Menu::Option::Stats)) {

            LCD.SetFontColor(WHITE);
            LCD.WriteAt("\"High\" score: 253", 0, 40);
            LCD.WriteAt("Best 40 line time: 3:42", 0, 70);
            LCD.WriteAt("Total Lines cleared: 512", 0, 100);
        }
        if (mainMenu.isPageActive(Menu::Option::Credits)) {

            LCD.SetFontColor(WHITE);
            LCD.WriteAt("Tetrio++ Written by:", 0, 20);
            LCD.WriteAt("Nathan Cheng", 0, 50);
            LCD.WriteAt("Ojas Landge", 0, 90);
        }

        if (mainMenu.isPageActive(Menu::Option::Instructions)) {

            LCD.SetFontColor(WHITE);
            LCD.WriteAt("How to play Tetrio++", 0, 20);
            LCD.WriteAt("The goal is to clear lines", 0, 50);
            LCD.WriteAt("faster than your opponent.", 0, 90);
            LCD.WriteAt("First to stack to the", 0, 120);
            LCD.WriteAt("top loses", 0, 150);
        }

        mainMenu.update();

        // board1.drawMino(0,0);

        LCD.Update();

        // debug mouse pointer
        // LPPOINT point;
        // GetCursorPos(point);
    }

    return 0;
}
