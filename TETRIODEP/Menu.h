#pragma once

#include "Button.h"
#include "Grid.h"
#include "TETRIODEP/Options.h"
#include "TETRIODEP/TetrisBoard.h"

class Menu {
  private:
  int buttonoffset = 50;
  public:
  bool onStartclicked;

    Button start;
    Button settings;
    Button stats;
    Button instructions;
    Button credits;
    Button back;

    //main logic
    int board1Loc[2] = {40, 220};
    int board2Loc[2] = {200, 220};

    Settings set = defaultSettings;;
    TetrisBoard board1;
    TetrisBoard board2;
    Options optionsPage;



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

    void run();

    void remove();
};
