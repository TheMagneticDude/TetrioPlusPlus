#include <limits>
#include <string>

#include "Button.h"
#include <FEHLCD.h>

using namespace std;

unsigned int defaultNormColor = WHITE;
unsigned int defaultTriggeredColor = GRAY;
unsigned int defaultDisabledColor = 0x212121;

Button::Button() {}
Button::Button(float x, float y, string text) {

    buttonX = x;
    buttonY = y;
    
    buttonWidth = text.length() * LCD.getCharWidth();
    buttonHeight = LCD.getCharHeight();

    buttonText = text;

    triggered = false;
    enabled = true;

    defaultColor = defaultNormColor;
    triggeredColor = defaultTriggeredColor;
    disabledColor = defaultDisabledColor;

    removed = false;

    currColor = defaultColor;
}
// creates a rectangular button with x and y being the top left of the rectangle
Button::Button(float x, float y, float w, float h, string text) {

    buttonX = x;
    buttonY = y;
    buttonCenterX = x + w / 2;
    buttonCenterY = y + h / 2;
    buttonWidth = w;
    buttonHeight = h;

    buttonText = text;

    triggered = false;
    enabled = true;

    defaultColor = defaultNormColor;
    triggeredColor = defaultTriggeredColor;
    disabledColor = defaultDisabledColor;

    removed = false;

    currColor = defaultColor;
}

// creates a rectangular button with x and y being the top left of the rectangle
Button::Button(float x, float y, float w, float h, string text, unsigned int color, unsigned int trigColor) {

    buttonX = x;
    buttonY = y;
    buttonCenterX = x + w / 2;
    buttonCenterY = y + h / 2;
    buttonWidth = w;
    buttonHeight = h;

    buttonText = text;

    triggered = false;
    enabled = true;

    defaultColor = color;
    triggeredColor = trigColor;
    disabledColor = defaultDisabledColor;

    removed = false;

    currColor = defaultColor;
}

Button::Button(float x, float y, string text, unsigned int color, unsigned int trigColor) {

    buttonX = x;
    buttonY = y;
    
    buttonWidth = text.length() * LCD.getCharWidth();
    buttonHeight = LCD.getCharHeight();

    buttonText = text;

    triggered = false;
    enabled = true;

    defaultColor = color;
    triggeredColor = trigColor;
    disabledColor = defaultDisabledColor;

    removed = false;

    currColor = defaultColor;
}

// initializes button values and whether button starts enabled or disabled
Button::Button(float x, float y, float w, float h, string text, bool e) {

    buttonX = x;
    buttonY = y;
    buttonCenterX = x + w / 2;
    buttonCenterY = y + h / 2;
    buttonWidth = w;
    buttonHeight = h;

    buttonText = text;

    triggered = false;
    enabled = e;

    defaultColor = defaultNormColor;
    triggeredColor = defaultTriggeredColor;
    disabledColor = defaultDisabledColor;
    removed = false;
    if (e) {
        currColor = disabledColor;
    } else {
        currColor = defaultColor;
    }
}

void Button::setDefaultColor(unsigned int color) { defaultColor = color; }
void Button::setTriggeredColor(unsigned int color) { triggeredColor = color; }
void Button::setDisabledColor(unsigned int color) { disabledColor = color; }

void Button::drawButton() {
    removed = false;
    LCD.SetFontColor(currColor);
    LCD.DrawRectangle(buttonX - LCD.getCharWidth(), buttonY, buttonWidth+ LCD.getCharWidth() * 2, buttonHeight);
    LCD.WriteAt(buttonText, buttonX, buttonY + 4);
}

// redraws button and also updates its state
void Button::updateButtonState() {
    if (enabled) {
        bool withinX = false;
        bool withinY = false;
        // update touched location
        if (!LCD.Touch(&touchedX, &touchedY, false)) {
            // wait until touch happens
        } else if (LCD.Touch(&xTrash, &yTrash, false)) {
            // wait until touch releases
            // no joke this is the actual code from FEH documentation -_-
            // if touch is within button boundery then set button state to true
            withinX = touchedX >= buttonX && touchedX <= buttonX + buttonWidth;
            withinY = touchedY >= buttonY && touchedY <= buttonY + buttonHeight;
        }
        if (withinX && withinY) {
            currColor = triggeredColor;
            // button is touched
            triggered = true;
            // toggle buttonState
            if (currState == buttonState::inactive) {
                currState = buttonState::active;
            }
            if (currState == buttonState::active) {
                currState = buttonState::held;
            }
        } else {
            currColor = defaultColor;
            // else clear touched location to off the screen
            triggered = false;
            touchedX = numeric_limits<float>::max();
            touchedY = numeric_limits<float>::max();

            // reset buttonState
            if (currState == buttonState::held) {
                currState = buttonState::released;
            }
            if (currState == buttonState::released) {
                currState = buttonState::inactive;
            }
        }
    }
    // redraws button
    drawButton();
}

bool Button::getButtonTriggered() { return triggered; }

bool Button::onButtonClicked() { return currState == buttonState::active; }

bool Button::onButtonReleased() { return currState == buttonState::released; }

void Button::disable() {
    enabled = false;
    currColor = disabledColor;
}

void Button::enable() {
    enabled = true;
    currColor = defaultColor;
}

void Button::remove() {
    if (!removed) {
        int backColor = BLACK;
        LCD.SetFontColor(backColor);
        LCD.DrawRectangle(buttonX, buttonY, buttonWidth, buttonHeight);
        LCD.WriteAt(buttonText, buttonX, buttonY + 4);
    }
    removed = true;
}
