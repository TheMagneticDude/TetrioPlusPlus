#include <limits>
#include <string>
#include "ToggleButton.h"
#include <FEHLCD.h>

using namespace std;

ToggleButton::ToggleButton() {}
//draws centered button
ToggleButton::ToggleButton(int y, string text, unsigned int color, unsigned int trigColor) {

    buttonX = (screenWidth/2.0) - ((text.length() / 2.0) * LCD.getCharWidth());
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
    //initializes time
    lastPress = std::chrono::high_resolution_clock::now();
}
ToggleButton::ToggleButton(float x, float y, string text) {

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
    //initializes time
    lastPress = std::chrono::high_resolution_clock::now();
}

ToggleButton::ToggleButton(float x, float y, string text, unsigned int color, unsigned int trigColor) {

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
    //initializes time
    lastPress = std::chrono::high_resolution_clock::now();
}


void ToggleButton::setDefaultColor(unsigned int color) { defaultColor = color; }
void ToggleButton::setTriggeredColor(unsigned int color) { triggeredColor = color; }
void ToggleButton::setDisabledColor(unsigned int color) { disabledColor = color; }

void ToggleButton::drawButton() {
    removed = false;
    LCD.SetFontColor(currColor);
    LCD.DrawRectangle(buttonX - LCD.getCharWidth(), buttonY, buttonWidth + LCD.getCharWidth() * 2, buttonHeight);
    LCD.WriteAt(buttonText, buttonX, buttonY + 4);
}

// redraws button and also updates its state
void ToggleButton::updateButtonState() {
    //update button to fit text
    buttonWidth = buttonText.length() * LCD.getCharWidth();
    buttonHeight = LCD.getCharHeight();

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
            auto currTime = std::chrono::high_resolution_clock::now();
            float debounceTime = 0.1; // debounce time in seconds
            if (std::chrono::duration<float>(currTime - lastPress).count() > debounceTime) {
                if (currState == buttonState::inactive) {
                    currState = buttonState::active;
                } else if (currState == buttonState::active) {
                    currState = buttonState::held;
                }
                currColor = triggeredColor;
                // button is touched
                triggered = !triggered;
                // toggle buttonState
                lastPress = std::chrono::high_resolution_clock::now();
            }
            } else if(!triggered){
                // no touch
                if (currState == buttonState::held) {
                    currState = buttonState::released;
                } else if (currState == buttonState::released) {
                    currState = buttonState::inactive;
                }
                currColor = defaultColor;
                // else clear touched location to off the screen
                triggered = false;
                touchedX = numeric_limits<float>::max();
                touchedY = numeric_limits<float>::max();

                // reset buttonState
            }
    }
    // redraws button
    drawButton();
}

bool ToggleButton::getButtonTriggered() { return triggered; }

bool ToggleButton::onButtonClicked() {
    bool clicked = false;
    if (currState == buttonState::active) {
        currState = buttonState::held;
        clicked = true;
    }
    return clicked;
}

bool ToggleButton::onButtonReleased() {
    bool released = false;
    if (currState == buttonState::released) {
        currState = buttonState::inactive;
        released = true;
    }
    return released;
}

void ToggleButton::disable() {
    enabled = false;
    currColor = disabledColor;
}

void ToggleButton::enable() {
    enabled = true;
    currColor = defaultColor;
}

void ToggleButton::setTriggered(bool t){
    triggered = t;
    if(t){
        currState == buttonState::held;
    }else{
        currState == buttonState::released;
    }
}

void ToggleButton::flashRed(){
    currColor = RED;
}

void ToggleButton::setString(std::string s){
    buttonText = s;
}

void ToggleButton::recenter(){
    buttonX = (screenWidth/2.0) - ((buttonText.length() / 2.0) * LCD.getCharWidth());
}


void ToggleButton::remove() {
    if (!removed) {
        int backColor = BLACK;
        LCD.SetFontColor(backColor);
        LCD.DrawRectangle(buttonX, buttonY, buttonWidth, buttonHeight);
        LCD.WriteAt(buttonText, buttonX, buttonY + 4);
    }
    removed = true;
}
