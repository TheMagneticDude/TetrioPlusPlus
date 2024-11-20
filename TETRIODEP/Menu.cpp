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
      settings(10, 20, 20, 20, "Settings"),
      stats(10, 30, 20, 20, "Stats"),
      instructions(10, 40, 20, 20, "Instructions"),
      credits(10, 50, 20, 20, "Credits") {
    //initialize button instances
};

void Menu::update(){
    start.updateButtonState();
    //settings.updateButtonState();
    //stats.updateButtonState();
    //instructions.updateButtonState();
    //credits.updateButtonState();

    if(start.getButtonTriggered()){
        
    }

}