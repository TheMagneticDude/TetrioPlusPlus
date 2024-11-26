#include "Menu.h"
#include "Button.h"
#include "Switch.h"

#include <FEHLCD.h>
#include <string>

#include <iostream>


Menu::Menu()
    : start(0 + buttonoffset, "Start", BLUE, DARKBLUE),
    stats(30 + buttonoffset, "Stats", BLUE, DARKBLUE), 
    settings(60 + buttonoffset, "Settings", BLUE, DARKBLUE),
      instructions(90 + buttonoffset, "Instructions", BLUE, DARKBLUE),
      credits(120 + buttonoffset, "Credits", BLUE, DARKBLUE), back(10, 0, "Back", BLUE, DARKBLUE),
      board1(board1Loc[0], board1Loc[1], set.p1Settings),
      board2(board2Loc[0], board2Loc[1], set.p2Settings),
      optionsPage(set)
      {
          // initialize button instances
          onStartclicked = false;

          
      };

void Menu::disable(Button &b) { b.disable(); }

void Menu::update() {

    if (currOption == Option::Back) {
        currOption = Option::None;
    }
    bool menuActive = currOption == Option::None; // if in subpage

    if (menuActive) {
        // removes back button and draws menu buttons
        start.updateButtonState();
        settings.updateButtonState();
        stats.updateButtonState();
        instructions.updateButtonState();
        credits.updateButtonState();

        // update current option selected if a button triggers
        if ((renderSubPage(start))) {
            
            if(currOption != Option::Start){
                currOption = Option::Start;
                onStartclicked = true;
            }else{
                onStartclicked = false;
            }
            
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
        // removes menu buttons and draws back button
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

    return b.onButtonReleased();
}

bool Menu::isPageActive(Option page){
    return currOption == page;
}

void Menu::renderBackButton() { back.updateButtonState(); }

void Menu::removeBack() { back.remove(); }

void Menu::remove() {
    // clears all menu buttons
    start.remove();
    settings.remove();
    stats.remove();
    instructions.remove();
    credits.remove();
}

void Menu::returnToMenu(){
    currOption = Option::Back;
            back.remove();
            // back to menu
}


//moved logic from main to here
void Menu::run(){
    update();

    if (isPageActive(Menu::Option::Start)) {

        if (onStartclicked) {
            // creates new boards with updated settings
            board1 = TetrisBoard(board1Loc[0], board1Loc[1], set.p1Settings);
            board2 = TetrisBoard(board2Loc[0], board2Loc[1], set.p2Settings);

            onStartclicked = false;
        }


            LCD.SetFontColor(WHITE);
            LCD.WriteAt("\"Play\" Tetrio++ below!", 25, 25);
            remove();

            board1.update();
            board2.update();

            board1.draw();
            board2.draw();

            //exit if game ends
            if(board1.gameEnded() || board2.gameEnded()){
                returnToMenu();
            }

        }
        if (isPageActive(Menu::Option::Settings)) {
            optionsPage.update();
        }

        if (isPageActive(Menu::Option::Stats)) {

            LCD.SetFontColor(WHITE);
            LCD.WriteAt("\"High\" score: 253", 0, 40);
            LCD.WriteAt("Best 40 line time: 3:42", 0, 70);
            LCD.WriteAt("Total Lines cleared: 512", 0, 100);
        }
        if (isPageActive(Menu::Option::Credits)) {

            LCD.SetFontColor(WHITE);
            LCD.WriteAt("Tetrio++ Written by:", 0, 20);
            LCD.WriteAt("Nathan Cheng", 0, 50);
            LCD.WriteAt("Ojas Landge", 0, 90);
        }

        if (isPageActive(Menu::Option::Instructions)) {

            LCD.SetFontColor(WHITE);
            LCD.WriteAt("How to play Tetrio++", 0, 20);
            LCD.WriteAt("The goal is to clear lines", 0, 50);
            LCD.WriteAt("faster than your opponent.", 0, 90);
            LCD.WriteAt("First to stack to the", 0, 120);
            LCD.WriteAt("top loses", 0, 150);
        }

}