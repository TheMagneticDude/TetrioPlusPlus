#include <FEHLCD.h>
#include <FEHRandom.h>
#include <cstdint>
#include <optional>
#include <vector>

#include "../TETRIODEP/Grid.h"
#include "../TETRIODEP/Menu.h"
#include "../TETRIODEP/TetrisBoard.h"
#include "../TETRIODEP/Tetromino.h"
#include "../TETRIODEP/MovementBoard.h"

// for key and mouse input
#include <Windows.h>

int main() {
    int board1Loc[2] = {40, 60};
    int board2Loc[2] = {200, 60};
    TetrisBoard board1(board1Loc[0], board1Loc[1]);
    MovementBoard movement1(board1Loc[0], board1Loc[1]);
    movement1.setMovingTetromino(50,50,static_cast<Tetromino>(2), TetrominoOrientation::H);
    TetrisBoard board2(board2Loc[0], board2Loc[1]);
    MovementBoard movement2(board1Loc[0], board1Loc[1]);

    Menu mainMenu = Menu();

    while (1) {
        // Buttons  can set up button bindings etc later

        // VK_LEFT 	0x25 	LEFT ARROW key
        // VK_UP 	0x26 	UP ARROW key
        // VK_RIGHT 	0x27 	RIGHT ARROW key
        // VK_DOWN 	0x28 	DOWN ARROW key

        bool rotateMino = GetAsyncKeyState(VK_UP);
        bool arrowDown = GetAsyncKeyState(VK_DOWN);
        bool moveLeft = GetAsyncKeyState(VK_LEFT);
        bool moveRight = GetAsyncKeyState(VK_RIGHT);

        // settings has not been implemented yet so disabled

        mainMenu.disable(mainMenu.settings);

        if (mainMenu.renderSubPage(mainMenu.start)) {
            LCD.SetFontColor(WHITE);
            LCD.WriteAt("\"Play\" Tetrio++ below!", 25, 25);
            mainMenu.remove();

            board1.draw();
            board2.draw();

            board1.drawTetromino(0, 0, static_cast<Tetromino>(2), TetrominoOrientation::H);
            board1.drawBorder();
            board2.drawBorder();

            //update movement
            movement1.update(moveLeft,moveRight,rotateMino,arrowDown);

            // if (moveLeft) {
            //     board1.drawRandom();
            // }
            // if (moveRight) {
            //     board2.drawRandom();
            // }
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

        if (mainMenu.renderSubPage(mainMenu.instructions)) {

            LCD.SetFontColor(WHITE);
            LCD.WriteAt("How to play Tetrio++", 0, 20);
            LCD.WriteAt("The goal is to clear lines", 0, 50);
            LCD.WriteAt("faster than your opponent.", 0, 90);
            LCD.WriteAt("First to stack to the", 0, 120);
            LCD.WriteAt("top looses", 0, 150);
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
