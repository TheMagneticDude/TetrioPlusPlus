#pragma once

#include "Button.h"
#include "Grid.h"

class Menu {
  private:
  int buttonoffset = 50;
  public:
    Button start;
    Button settings;
    Button stats;
    Button instructions;
    Button credits;
    Button back;



//had to make option enum visible to call isPageActive
enum class Option {
        None, // back to menu
        Start,
        Settings, // can include page for player names, controls, themes, etcs
        Stats,
        Instructions,
        Credits,
        Back, // limbo after back is pressed
    };

    // current option selected
    Option currOption = Option::None;


    Menu();
    bool renderSubPage(Button &b);
    bool isPageActive(Option page);
    void disable(Button &b);
    void update();

    void renderBackButton();
    void removeBack();

    void remove();
};
