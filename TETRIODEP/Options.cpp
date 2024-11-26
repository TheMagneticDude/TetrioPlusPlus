#include <chrono>

#include "Input.h"
#include "Options.h"
#include "Settings.h"
#include "ToggleButton.h"

#include <iostream>

Options::Options(Settings &set)
    : left(0 + buttonoffset, "Move Left: Default", BLUE, DARKBLUE), 
    right(20 + buttonoffset, "Move Right: Default", BLUE, DARKBLUE),
      softDrop(40 + buttonoffset, "Soft Drop: Default", BLUE, DARKBLUE),
      hardDrop(60 + buttonoffset, "Hard Drop: Default", BLUE, DARKBLUE),
      rotateCCW(80 + buttonoffset, "Rotate CCW: Default", BLUE, DARKBLUE),
      rotateCW(100 + buttonoffset, "Rotate CW: Default", BLUE, DARKBLUE),
      rotate180(120 + buttonoffset, "Rotate 180: Default", BLUE, DARKBLUE),
      swapHold(140 + buttonoffset, "Swap Hold: Default", BLUE, DARKBLUE), 
      p1Input(set.p1Settings), 
      p2Input(set.p2Settings),
      togglePlayer(10,"P1", BLUE,GRAY,8,6)
       {
    settings = &set;
    //initialize currSetting
    currSetting = &(settings->p1Settings);
    //initialize pointer
    currentPlayerInput = &p1Input;
    //update buttons to match their default 
    updateButtonNames();
    
}

void Options::update() {
    //update switch
    togglePlayer.update();
    if(togglePlayer.getToggled()){
        currentPlayerInput = &p2Input;
        togglePlayer.setString("P2");
        currSetting = &(settings->p2Settings);
        updateButtonNames();
    }else{
        currentPlayerInput = &p1Input;
        togglePlayer.setString("P1");
        currSetting = &(settings->p1Settings);
        updateButtonNames();
    }

    // update all button states
    left.updateButtonState();
    right.updateButtonState();
    softDrop.updateButtonState();
    hardDrop.updateButtonState();
    rotateCCW.updateButtonState();
    rotateCW.updateButtonState();
    rotate180.updateButtonState();
    swapHold.updateButtonState();

    //recenter all buttons
    left.recenter();
    right.recenter();
    softDrop.recenter();
    hardDrop.recenter();
    rotateCCW.recenter();
    rotateCW.recenter();
    rotate180.recenter();
    swapHold.recenter();

    

    // deboucnce
    bool buttonClicked = left.onButtonClicked() || right.onButtonClicked() || softDrop.onButtonClicked() ||
                         hardDrop.onButtonClicked() || rotateCCW.onButtonClicked() || rotateCW.onButtonClicked() ||
                         rotate180.onButtonClicked() || swapHold.onButtonClicked();
    if (buttonClicked) {
        lastPress = std::chrono::high_resolution_clock::now();
    }

    auto currTime = std::chrono::high_resolution_clock::now();

    // only let run if enough time has passed
    // to prevent keys from being read too often
    float debounceTime = 0.1; // debounce time in seconds
    if (std::chrono::duration<float>(currTime - lastPress).count() > debounceTime) {
        //if no buttons are toggled then reset to none
        if(!anyButtonToggled()){
            currActive = buttons::none;
        }

        if(currActive == buttons::none){
            getCurrentButton();
        }

        
        

        
        if (currActive == buttons::left) {
            handleButtonToggle(left);
            // gets first key pressed in the array read.
            // Will add support for multiple keys pressed at once eventually
            auto keys = currentPlayerInput->scanKey();
            if (!keys.empty()) {
                int key = keys.front();
                // currentPlayerInput->setKey(PlayerInput::KeyAction::MoveLeft, key);
                currSetting->controls.moveLeft = key;
                left.setTriggered(false);
                std::string keyString = getKeyName(key);
                left.setString("Move Left: " + keyString);
                currActive = buttons::none;
            }
        }
        if (currActive == buttons::right) {
            handleButtonToggle(right);
            auto keys = currentPlayerInput->scanKey();
            if (!keys.empty()) {
                int key = keys.front();
                currSetting->controls.moveRight = key;
                right.setTriggered(false);
                std::string keyString = getKeyName(key);
                right.setString("Move Right: " + keyString);
                currActive = buttons::none;
            }
        }
        if (currActive == buttons::softDrop) {
            handleButtonToggle(softDrop);
             auto keys = currentPlayerInput->scanKey();
            if (!keys.empty()) {
                int key = keys.front();
                currSetting->controls.softDrop = key;
                softDrop.setTriggered(false);
                std::string keyString = getKeyName(key);
                softDrop.setString("Soft Drop: " + keyString);
                currActive = buttons::none;
            }
        }
        if (currActive == buttons::hardDrop) {
            handleButtonToggle(hardDrop);
            auto keys = currentPlayerInput->scanKey();
            if (!keys.empty()) {
                int key = keys.front();
                currSetting->controls.hardDrop = key;
                hardDrop.setTriggered(false);
                std::string keyString = getKeyName(key);
                hardDrop.setString("Hard Drop: " + keyString);
                currActive = buttons::none;
            }
        }
        if (currActive == buttons::rotateCCW) {
            handleButtonToggle(rotateCCW);
            auto keys = currentPlayerInput->scanKey();
            if (!keys.empty()) {
                int key = keys.front();
                currSetting->controls.rotateCCW = key;
                rotateCCW.setTriggered(false);
                std::string keyString = getKeyName(key);
                rotateCCW.setString("Rotate CCW: " + keyString);
                currActive = buttons::none;
            }
        }
        if (currActive == buttons::rotateCW) {
            handleButtonToggle(rotateCW);
            auto keys = currentPlayerInput->scanKey();
            if (!keys.empty()) {
                int key = keys.front();
                currSetting->controls.rotateCW = key;
                rotateCW.setTriggered(false);
                std::string keyString = getKeyName(key);
                rotateCW.setString("Rotate CW: " + keyString);
                currActive = buttons::none;
            }
        }
        if (currActive == buttons::rotate180) {
            handleButtonToggle(rotate180);
            auto keys = currentPlayerInput->scanKey();
            if (!keys.empty()) {
                int key = keys.front();
                currSetting->controls.rotate180 = key;
                rotate180.setTriggered(false);
                std::string keyString = getKeyName(key);
                rotate180.setString("Rotate 180: " + keyString);
                currActive = buttons::none;
            }
        }
        if (currActive == buttons::swapHold) {
            handleButtonToggle(swapHold);
            auto keys = currentPlayerInput->scanKey();
            if (!keys.empty()) {
                int key = keys.front();
                currSetting->controls.swapHold = key;
                swapHold.setTriggered(false);
                std::string keyString = getKeyName(key);
                swapHold.setString("Swap Hold: " + keyString);
                currActive = buttons::none;
            }
        }
    }
}

void Options::handleButtonToggle(ToggleButton &b){
    if (otherButtonToggled(b)) {
        b.flashRed();
        // Untoggle other buttons
        untoggleOthers(b);
    }
}

void Options::getCurrentButton(){
    //get current button that is toggled
        if(left.getButtonTriggered()){
            currActive = buttons::left;
        }else if(right.getButtonTriggered()){
            currActive = buttons::right;
        }else if(softDrop.getButtonTriggered()){
            currActive = buttons::softDrop;
        }else if(hardDrop.getButtonTriggered()){
            currActive = buttons::hardDrop;
        }else if(rotateCCW.getButtonTriggered()){
            currActive = buttons::rotateCCW;
        }else if(rotateCW.getButtonTriggered()){
            currActive = buttons::rotateCW;
        }else if(rotate180.getButtonTriggered()){
            currActive = buttons::rotate180;
        }else if(swapHold.getButtonTriggered()){
            currActive = buttons::swapHold;
        }else{
            currActive = buttons::none;
        }
}

// untoggles all other buttons
void Options::untoggleOthers(ToggleButton &b) {
    ToggleButton *buttons[] = {&left, &right, &softDrop, &hardDrop, &rotateCCW, &rotateCW, &rotate180, &swapHold};

    for (ToggleButton *TB : buttons) {
        if (TB != &b) {
            TB->setTriggered(false);
        }
    }
}

// checks if other buttons ar toggled
bool Options::otherButtonToggled(ToggleButton &b) {

    ToggleButton *buttons[] = {&left, &right, &softDrop, &hardDrop, &rotateCCW, &rotateCW, &rotate180, &swapHold};

    for (ToggleButton *TB : buttons) {
        if (TB != &b && TB->getButtonTriggered()) {
            return true;
        }
    }
    return false;
}

bool Options::anyButtonToggled(){
    ToggleButton *buttons[] = {&left, &right, &softDrop, &hardDrop, &rotateCCW, &rotateCW, &rotate180, &swapHold};

    for (ToggleButton *TB : buttons) {
        if (TB->getButtonTriggered()) {
            return true;
        }
    }
    return false;
}

std::string Options::getKeyName(int key){
    return keyNameMap[key];
}

void Options::updateButtonNames(){
    left.setString("Move Left: " + getKeyName(currSetting->controls.moveLeft));
    right.setString("Move Right: " + getKeyName(currSetting->controls.moveRight));
    softDrop.setString("Soft Drop: " + getKeyName(currSetting->controls.softDrop));
    hardDrop.setString("Hard Drop: " + getKeyName(currSetting->controls.hardDrop));
    rotateCCW.setString("Rotate CCW: " + getKeyName(currSetting->controls.rotateCCW));
    rotateCW.setString("Move Left: " + getKeyName(currSetting->controls.rotateCW));
    rotate180.setString("Rotate 180: " + getKeyName(currSetting->controls.rotate180));
    swapHold.setString("Swap Hold: " + getKeyName(currSetting->controls.swapHold));
}

void Options::remove() {
    // clears all option buttons
    left.remove();
    right.remove();
    softDrop.remove();
    hardDrop.remove();
    rotateCCW.remove();
    rotateCW.remove();
    rotate180.remove();
    swapHold.remove();
}
