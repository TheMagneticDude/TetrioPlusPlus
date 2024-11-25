#pragma once

#include <string>

#include "Grid.h"
#include <FEHLCD.h>

using namespace std;

class Button {
  private:
    const unsigned int screenWidth = 320;
    const unsigned int screenHeight = 240;

    const unsigned int defaultNormColor = WHITE;
    const unsigned int defaultTriggeredColor = GRAY;
    const unsigned int defaultDisabledColor = 0x212121;

    enum class buttonState { inactive, active, held, released };

    buttonState currState = buttonState::inactive;

    bool triggered; // if button is being held it is true
    bool enabled;   // if button can be pressed it is true

    int defaultColor;   // normal color of button
    int triggeredColor; // color of button when triggered
    int disabledColor;  // color of button when disabled

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

    bool removed;

    Button();
    //creates centered button
    Button(int y, string text, unsigned int color, unsigned int trigColor);
    Button(float x, float y, string text);
    Button(float x, float y, float w, float h, string text);
    Button(float x, float y, float w, float h, string text, unsigned int color, unsigned int trigColor);
    Button(float x, float y, string text, unsigned int color, unsigned int trigColor);
    Button(float x, float y, float w, float h, string text, bool e);

    void drawButton();

    void setDefaultColor(unsigned int color);
    void setTriggeredColor(unsigned int color);
    void setDisabledColor(unsigned int color);
    void updateButtonState();

    bool getButtonTriggered();

    // returns true once when button is pressed and doesent return true again until its been let go and then pressed
    // again
    bool onButtonClicked();

    // returns true once when button is released
    bool onButtonReleased();

    void disable();
    void enable();

    void remove();
};
