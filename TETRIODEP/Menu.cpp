#include "../TETRIODEP/Menu.h"
#include "../TETRIODEP/Button.h"
#include "../TETRIODEP/Grid.h"
#include "../TETRIODEP/TetrisBoard.h"
#include "../TETRIODEP/Tetromino.h"
#include "FEHRandom.h"

#include <FEHLCD.h>
#include <iostream>
#include <string>

Menu::Menu() 
    : start(0, 0, 70, 20, "Start"),
      settings(10, 90, 70, 20, "Settings"),
      stats(10, 110, 70, 20, "Stats"),
      instructions(10, 130, 70, 20, "Instructions"),
      credits(10, 150, 70, 20, "Credits") {
    //initialize button instances
};

void Menu::update(){
    start.updateButtonState();
    settings.updateButtonState();
    stats.updateButtonState();
    instructions.updateButtonState();
    credits.updateButtonState();
}

void Menu::remove(){
    start.remove();
    settings.remove();
    stats.remove();
    instructions.remove();
    credits.remove();
}