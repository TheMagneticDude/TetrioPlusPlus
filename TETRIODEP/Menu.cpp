#include "../TETRIODEP/Menu.h"
#include "../TETRIODEP/Button.h"
#include "../TETRIODEP/Grid.h"
#include "../TETRIODEP/TetrisBoard.h"
#include "../TETRIODEP/Tetromino.h"
#include "FEHRandom.h"

#include <FEHLCD.h>
#include <iostream>
#include <string>

int buttonoffset = 30;

Menu::Menu()
    : start(10, 0+buttonoffset, 70, 20, "Start", BLUE, DARKBLUE), settings(10, 30+buttonoffset, 70, 20, "Settings", BLUE, DARKBLUE),
      stats(10, 60+buttonoffset, 70, 20, "Stats", BLUE, DARKBLUE), instructions(10, 90+buttonoffset, 70, 20, "Instructions", BLUE, DARKBLUE),
      credits(10, 120+buttonoffset, 70, 20, "Credits", BLUE, DARKBLUE), back(10, 0, 40, 20, "Back", BLUE, DARKBLUE) {
    // initialize button instances

    // by default menue has not clicked into a page yet
    inPage = false;
};

void Menu::disable(Button &b) { b.disable(); }

void Menu::update() {

  if(currOption == Option::Back){
    //clears screen loop right after back is clicked
    LCD.Clear();
    currOption = Option::None;
  }
    bool menuActive = currOption == Option::None; //if in subpage
    

    if (menuActive) {
      //removes back button and draws menu buttons
        start.updateButtonState();
        settings.updateButtonState();
        stats.updateButtonState();
        instructions.updateButtonState();
        credits.updateButtonState();

        // update current option selected if a button triggers
    if (renderSubPage(start)) {
        currOption = Option::Start;
    }
    if (renderSubPage(settings)) {
        currOption = Option::Settings;
    }
    if (renderSubPage(stats)) {
        currOption = Option::Stats;
    }
    if (renderSubPage(instructions)) {
        currOption = Option::Instructions;
    }
    if (renderSubPage(credits)) {
        currOption = Option::Credits;
    }
    } else {
      //removes menu buttons and draws back button
        remove();
        back.updateButtonState();

        if (renderSubPage(back)) {
        currOption = Option::Back;
        back.remove();
        // back to menu
    }
    }

    
    
}

// returns true when its time to render a subpage for a given button
bool Menu::renderSubPage(Button &b) {
    bool render = false;
    if (b.getButtonTriggered()) {
        //  clear main menu screen
        if (b.onButtonClicked()) {
            LCD.Clear();
        }
        render = true;
    } else if (b.onButtonReleased()) {
        LCD.Clear();
    }
    return render;
}

void Menu::renderBackButton() { back.updateButtonState(); }

void Menu::removeBack() { back.remove(); }

void Menu::remove() {
  //clears all menu buttons
    start.remove();
    settings.remove();
    stats.remove();
    instructions.remove();
    credits.remove();
}