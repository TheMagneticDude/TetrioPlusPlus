#pragma once

#include "Button.h"
#include "Grid.h"
#include "Options.h"
#include "TetrisBoard.h"
#include <FEHImages.h>

class Menu {
  private:
  unsigned int screenWidth = 320;
  unsigned int screenHeight = 240;

  int buttonoffset = 70;
  public:
  bool onStartclicked;
  bool onSingleClicked;

    Button start;
    Button singleplayer;
    Button settings;
    Button stats;
    Button instructions;
    Button credits;
    Button back;

    //main logic
    int board1Loc[2] = {50, 220};
    int board2Loc[2] = {210, 220};

    int singleBoardLoc[2] = {80,220};

    bool gameEnded;

    Settings set = defaultSettings;
    Statistics playerStats = statistics;
    TetrisBoard board1;
    TetrisBoard board2;
    TetrisBoard singleBoard;
    Options optionsPage;

    FEHImage menuBackground;
    FEHImage playBackground;
    FEHImage confetti;
    FEHImage creditsImage;
    FEHImage howToPlay;



    //had to make option enum visible to call isPageActive
    enum class MenuOption {
        None_, // back to menu
        Start,
        Single,//singleplayer 40 line
        Settings, // can include page for player names, controls, themes, etcs
        Stats,
        Instructions,
        Credits,
        Back, // limbo after back is pressed
    };

    // current option selected
    MenuOption currOption = MenuOption::None_;


    Menu();
    bool renderSubPage(Button &b);
    bool isPageActive(MenuOption page);
    void disable(Button &b);
    void update();

    void renderBackButton();
    void removeBack();

    void returnToMenu();



    void run();

    void remove();
};
