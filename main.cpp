#include "TETRIODEP/Menu.h"
#include "TETRIODEP/TetrisBoard.h"
#include "TETRIODEP/Options.h"
#include <FEHLCD.h>
#include <FEHRandom.h>

int main() {
    Settings settings = defaultSettings;

    int board1Loc[2] = {40, 220};
    int board2Loc[2] = {200, 220};
    TetrisBoard board1(board1Loc[0], board1Loc[1], settings.p1Settings);
    
    TetrisBoard board2(board2Loc[0], board2Loc[1], settings.p2Settings);
    
    // Options page (set up for p1 for now ill create sliders and switches to change later)
    Options optionsPage = Options(settings.p1Settings);

    Menu mainMenu = Menu();

    while (1) {
        LCD.Clear();
        mainMenu.update();


        if (mainMenu.isPageActive(Menu::Option::Start)) {
            LCD.SetFontColor(WHITE);
            LCD.WriteAt("\"Play\" Tetrio++ below!", 25, 25);
            mainMenu.remove();

            board1.update();
            board2.update();

            board1.draw();
            board2.draw();   
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

        LCD.Update();
    }

    

    return 0;
}
