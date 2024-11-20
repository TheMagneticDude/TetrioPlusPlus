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
}

void Button::setDefaultColor(int color){defaultColor = color;}
void Button::setTriggeredColor(int color){triggeredColor = color;}
void Button::setDisabledColor(int color){disabledColor = color;}

void Button::drawButton(){
    LCD.SetFontColor(defaultColor);
    LCD.DrawRectangle(buttonX,buttonY,buttonWidth,buttonHeight);
    LCD.WriteAt(buttonText,buttonX,buttonY+4);
}

//redraws button and also updates its state
void Button::updateButtonState(){
    drawButton();
    //update touched location
    if(!LCD.Touch(&touchedX,&touchedY)){
        //wait until touch happens
    }else
    if(LCD.Touch(&xTrash,&yTrash)){
        //wait until touch releases
        //no joke this is the actual code from FEH documentation -_-
        //if touch is within button boundery then set button state to true
    bool withinX = touchedX >= buttonX && touchedX <= buttonX + buttonWidth;
    bool withinY = touchedY >= buttonY && touchedY <= buttonY + buttonHeight;
    if(withinX && withinY){
        //button is touched
        triggered = true;
        cout<<"PRESSED";
    }else{
        //else clear touched location to off the screen
        triggered = false;
        touchedX = numeric_limits<float>::max();
        touchedY = numeric_limits<float>::max();
    }
    }
    
}

bool Button::getButtonTriggered(){
    return triggered;
}

