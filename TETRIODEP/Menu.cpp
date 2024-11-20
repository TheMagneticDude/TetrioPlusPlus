#include "../TETRIODEP/Menu.h"
#include "../TETRIODEP/Button.h"
#include "../TETRIODEP/Grid.h"
#include "../TETRIODEP/TetrisBoard.h"
#include "../TETRIODEP/Tetromino.h"
#include "FEHRandom.h"

#include <FEHLCD.h>
#include <iostream>
#include <string>

Menu::Menu() : start(0, 0, 70, 20, "Start") {
    
};

void Menu::update(){
    start.updateButtonState();
    settings.updateButtonState();
    stats.updateButtonState();
    instructions.updateButtonState();
    credits.updateButtonState();

    if(start.getButtonTriggered()){
        
    }

}