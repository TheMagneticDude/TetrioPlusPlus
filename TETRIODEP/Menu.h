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
  enum Option currOption = Option::None;
  public:
    Button start;// = Button(0, 0, 70, 20, "Start");
    Button settings = Button(10, 20, 20, 20, "Settings");
    Button stats = Button(10, 30, 20, 20, "Stats");
    Button instructions = Button(10, 40, 20, 20, "Instructions");
    Button credits = Button(10, 50, 20, 20, "Start");
  Menu();
  void update();
    
    };
#endif