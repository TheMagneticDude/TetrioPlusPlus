#pragma once
#include "../TETRIODEP/Button.h"
#include "../TETRIODEP/Grid.h"
class Menu {
  private:
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

    bool inPage;

  public:
    Button start;
    Button settings;
    Button stats;
    Button instructions;
    Button credits;
    Button back;

    Menu();
    bool renderSubPage(Button &b);
    void disable(Button &b);
    void update();

    void renderBackButton();
    void removeBack();

    void remove();
};
