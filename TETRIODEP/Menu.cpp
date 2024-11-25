#include "Menu.h"
#include "Button.h"

#include <FEHLCD.h>
#include <string>

#include <iostream>


Menu::Menu()
    : start(0 + buttonoffset, "Start", BLUE, DARKBLUE),
    stats(30 + buttonoffset, "Stats", BLUE, DARKBLUE), 
    settings(60 + buttonoffset, "Settings", BLUE, DARKBLUE),
      instructions(90 + buttonoffset, "Instructions", BLUE, DARKBLUE),
      credits(120 + buttonoffset, "Credits", BLUE, DARKBLUE), back(10, 0, "Back", BLUE, DARKBLUE) {
          // initialize button instances
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