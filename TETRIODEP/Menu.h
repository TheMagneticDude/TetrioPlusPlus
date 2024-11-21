#ifndef MENU.H
#define MENU .H

#include "../TETRIODEP/Grid.h"
#include "../TETRIODEP/Button.h"
class Menu {
  private:
  enum class Option{
    None,
    Start,
    Settings,//can include page for player names, controls, themes, etcs
    Stats,
    Instructions,
    Credits,
  };

//current option selected
  Option currOption = Option::None;
  public:
    Button start;
    Button settings;
    Button stats;
    Button instructions;
    Button credits;
  Menu();
  void update();

  void remove();
    
    };
#endif