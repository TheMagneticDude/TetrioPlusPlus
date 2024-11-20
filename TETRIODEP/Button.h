#ifndef BUTTON.H
#define BUTTON .H

#include "../TETRIODEP/Grid.h"
#include <FEHLCD.h>
#include <string>
using namespace std;

class Button {
  private:
  bool triggered; //if button is being held it is true
  bool enabled; //if button can be pressed it is true

  int defaultColor;//normal color of button
  int triggeredColor;//color of button when triggered
  int disabledColor;//color of button when disabled

  int currColor = defaultColor;

  public:
  float buttonX;
  float buttonY;

  float touchedX;
  float touchedY;
  float xTrash;
  float yTrash;

  float buttonCenterX;
  float buttonCenterY;

  float buttonWidth;
  float buttonHeight;

  string buttonText;

  Button();
  Button(float x, float y, float w, float h, string text);
  Button(float x, float y, float w, float h, string text, bool e);

  void drawButton();

  void setDefaultColor(int color);
  void setTriggeredColor(int color);
  void setDisabledColor(int color);
  void updateButtonState();

  bool getButtonTriggered();

  
};
#endif