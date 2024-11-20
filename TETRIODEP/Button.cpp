#include "../TETRIODEP/TetrisBoard.h"
#include "../TETRIODEP/Grid.h"
#include "../TETRIODEP/Tetromino.h"
#include "../TETRIODEP/Button.h"
#include "FEHRandom.h"
#include <FEHLCD.h>
#include "../TETRIODEP/Button.h"

#include <iostream>
#include <string>
#include <limits>

using namespace std;

Button::Button(){}
//creates a rectangular button with x and y being the top left of the rectangle
Button::Button(float x, float y, float w, float h,string text){

    buttonX = x;
    buttonY = y;
    buttonCenterX = x + w/2;
    buttonCenterY = y + h/2;
    buttonWidth = w;
    buttonHeight = h;

    buttonText = text;


    triggered = false;
    enabled = true;
    
    defaultColor = WHITE;
    triggeredColor = GRAY;
    disabledColor = DARKGRAY;
    
    currColor = defaultColor;
}


//initializes button values and whether button starts enabled or disabled
Button::Button(float x, float y, float w, float h,string text, bool e){

    buttonX = x;
    buttonY = y;
    buttonCenterX = x + w/2;
    buttonCenterY = y + h/2;
    buttonWidth = w;
    buttonHeight = h;

    buttonText = text;


    triggered = false;
    enabled = e;
    
    defaultColor = WHITE;
    triggeredColor = GRAY;
    disabledColor = DARKGRAY;
    if(e){
    currColor=disabledColor;
    }else{
        currColor = defaultColor;
    }
}

void Button::setDefaultColor(int color){defaultColor = color;}
void Button::setTriggeredColor(int color){triggeredColor = color;}
void Button::setDisabledColor(int color){disabledColor = color;}

void Button::drawButton(){
    LCD.SetFontColor(currColor);
    LCD.DrawRectangle(buttonX,buttonY,buttonWidth,buttonHeight);
    LCD.WriteAt(buttonText,buttonX,buttonY+4);
}

//redraws button and also updates its state
void Button::updateButtonState(){
    bool withinX = false;
    bool withinY = false;
    //update touched location
    if(!LCD.Touch(&touchedX,&touchedY)){
        //wait until touch happens
    }else
    if(LCD.Touch(&xTrash,&yTrash)){
        //wait until touch releases
        //no joke this is the actual code from FEH documentation -_-
        //if touch is within button boundery then set button state to true
    withinX = touchedX >= buttonX && touchedX <= buttonX + buttonWidth;
    withinY = touchedY >= buttonY && touchedY <= buttonY + buttonHeight;
    }
    if(withinX && withinY){
        //button is touched
        triggered = true;
        //trigger color change
        currColor = triggeredColor;

        //toggle buttonState
        if(currState == buttonState::inactive){
            currState = buttonState::active;
        }
        if(currState == buttonState::active){
            currState = buttonState::held;
        }
        cout<<"PRESSED";
    }else{
        //else clear touched location to off the screen
        triggered = false;
        //reset color
        currColor = defaultColor;
        touchedX = numeric_limits<float>::max();
        touchedY = numeric_limits<float>::max();

        //reset buttonState
        if(currState == buttonState::held){
            currState = buttonState::released;
        }
        if(currState == buttonState::released){
            currState = buttonState::inactive;
        }
    }
    //redraws button
    drawButton();

    
}

bool Button::getButtonTriggered(){
    return triggered;
}

bool Button::onButtonClicked(){
    return currState == buttonState::active;
}

bool Button::onButtonReleased(){
    return currState == buttonState::released;
}

