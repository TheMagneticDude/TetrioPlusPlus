#include <chrono>

#include "Input.h"
#include "Options.h"
#include "Settings.h"
#include "ToggleButton.h"

Options::Options(Settings &set)
    : left(20 + buttonoffset, "Move Left: Default", BLUE, DARKBLUE),
      right(20 + buttonoffset, "Move Right: Default", BLUE, DARKBLUE),
      softDrop(40 + buttonoffset, "Soft Drop: Default", BLUE, DARKBLUE),
      hardDrop(60 + buttonoffset, "Hard Drop: Default", BLUE, DARKBLUE),
      rotateCCW(80 + buttonoffset, "Rotate CCW: Default", BLUE, DARKBLUE),
      rotateCW(100 + buttonoffset, "Rotate CW: Default", BLUE, DARKBLUE),
      rotate180(120 + buttonoffset, "Rotate 180: Default", BLUE, DARKBLUE),
      swapHold(140 + buttonoffset, "Swap Hold: Default", BLUE, DARKBLUE), p1Input(set.p1Settings),
      p2Input(set.p2Settings), togglePlayer(0, "P1", BLUE, GRAY, 8, 6), arr("ARR", 30, 200, 0, BLUE, DARKBLUE, 0, 5),
      das("DAS", 50, 200, 0, BLUE, DARKBLUE, 0, 1), dcd("DCD", 70, 200, 0, BLUE, DARKBLUE, 0, 1),
      sdf("SDF", 90, 200, 0, BLUE, DARKBLUE, 5, 40) {
    settings = &set;
    // initialize currSetting
    currSetting = &(settings->p1Settings);
    // initialize pointer
    currentPlayerInput = &p1Input;
    // update buttons to match their default
    updateButtonNames();
    updateSliderValues();
    switchToggled = false;
    wasToggled = false;
}

// Updates options page state and renders page
// Author: Nathan
void Options::update() {
    // update slides
    arr.update();
    das.update();
    dcd.update();
    sdf.update();
    // update switch
    togglePlayer.update();
    if (togglePlayer.getToggled()) {
        currentPlayerInput = &p2Input;
        togglePlayer.setString("P2");
        currSetting = &(settings->p2Settings);
        updateButtonNames();
        if (!wasToggled) {
            wasToggled = true;
            switchToggled = true;
            updateSliderValues();
        }

    } else {
        currentPlayerInput = &p1Input;
        togglePlayer.setString("P1");
        currSetting = &(settings->p1Settings);
        updateButtonNames();
        if (wasToggled) {
            wasToggled = false;
            switchToggled = false;
            updateSliderValues();
        }
    }

    // slider set values
    currSetting->handling.arr = arr.getValue();
    currSetting->handling.das = das.getValue();
    currSetting->handling.dcd = dcd.getValue();
    currSetting->handling.sdf = sdf.getValue();

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
        // if no buttons are toggled then reset to none
        if (!anyButtonToggled()) {
            currActive = buttons::none;
        }

        if (currActive == buttons::none) {
            getCurrentButton();
        }

        if (currActive == buttons::left) {
            left.setString("<Press Key>");
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
            right.setString("<Press Key>");
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
            softDrop.setString("<Press Key>");
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
            hardDrop.setString("<Press Key>");
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
            rotateCCW.setString("<Press Key>");
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
            rotateCW.setString("<Press Key>");
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
            rotate180.setString("<Press Key>");
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
            swapHold.setString("<Press Key>");
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

    // due to lack of space and me not wanting to implement scrolling lol
    // left and right need to be next to each other
    recenterButtonPair(left, right);

    // recenter all buttons
    //  left.recenter();
    //  right.recenter();
    softDrop.recenter();
    hardDrop.recenter();
    rotateCCW.recenter();
    rotateCW.recenter();
    rotate180.recenter();
    swapHold.recenter();

    // update all button states

    left.updateButtonState();
    right.updateButtonState();
    softDrop.updateButtonState();
    hardDrop.updateButtonState();
    rotateCCW.updateButtonState();
    rotateCW.updateButtonState();
    rotate180.updateButtonState();
    swapHold.updateButtonState();
}

// Flashes red if another button is pressed and untoggles all others
// Author: Nathan
void Options::handleButtonToggle(ToggleButton &b) {
    if (otherButtonToggled(b)) {
        b.flashRed();
        // Untoggle other buttons
        untoggleOthers(b);
    }
}
// Get current button that is toggled
// Author: Nathan
void Options::getCurrentButton() {

    if (left.getButtonTriggered()) {
        currActive = buttons::left;
    } else if (right.getButtonTriggered()) {
        currActive = buttons::right;
    } else if (softDrop.getButtonTriggered()) {
        currActive = buttons::softDrop;
    } else if (hardDrop.getButtonTriggered()) {
        currActive = buttons::hardDrop;
    } else if (rotateCCW.getButtonTriggered()) {
        currActive = buttons::rotateCCW;
    } else if (rotateCW.getButtonTriggered()) {
        currActive = buttons::rotateCW;
    } else if (rotate180.getButtonTriggered()) {
        currActive = buttons::rotate180;
    } else if (swapHold.getButtonTriggered()) {
        currActive = buttons::swapHold;
    } else {
        currActive = buttons::none;
    }
}

// Untoggles all other buttons
// Author: Nathan
void Options::untoggleOthers(ToggleButton &b) {
    ToggleButton *buttons[] = {&left, &right, &softDrop, &hardDrop, &rotateCCW, &rotateCW, &rotate180, &swapHold};

    for (ToggleButton *TB : buttons) {
        if (TB != &b) {
            TB->setTriggered(false);
        }
    }
}

// Checks if other buttons ar toggled
// Author: Nathan
bool Options::otherButtonToggled(ToggleButton &b) {

    ToggleButton *buttons[] = {&left, &right, &softDrop, &hardDrop, &rotateCCW, &rotateCW, &rotate180, &swapHold};

    for (ToggleButton *TB : buttons) {
        if (TB != &b && TB->getButtonTriggered()) {
            return true;
        }
    }
    return false;
}

// Checks if any other button is toggled
// Author: Nathan
bool Options::anyButtonToggled() {
    ToggleButton *buttons[] = {&left, &right, &softDrop, &hardDrop, &rotateCCW, &rotateCW, &rotate180, &swapHold};

    for (ToggleButton *TB : buttons) {
        if (TB->getButtonTriggered()) {
            return true;
        }
    }
    return false;
}

// Gets a the string name of a key if it exists
// Author: Nathan
std::string Options::getKeyName(int key) {
#ifdef _WIN32
    // if key exists as text return the key
    if (keyNameMap.find(key) != keyNameMap.end()) {
        return keyNameMap[key];
    }

    // returns UNKNOWN key
    return keyNameMap[-1];
#endif
#if __linux__ && !__ANDROID__
    return XKeysymToString(key);
#endif
}

// Updates button names
// Author: Nathan
void Options::updateButtonNames() {
    left.setString("Move Left: " + getKeyName(currSetting->controls.moveLeft));
    right.setString("Move Right: " + getKeyName(currSetting->controls.moveRight));
    softDrop.setString("Soft Drop: " + getKeyName(currSetting->controls.softDrop));
    hardDrop.setString("Hard Drop: " + getKeyName(currSetting->controls.hardDrop));
    rotateCCW.setString("Rotate CCW: " + getKeyName(currSetting->controls.rotateCCW));
    rotateCW.setString("Rotate CW: " + getKeyName(currSetting->controls.rotateCW));
    rotate180.setString("Rotate 180: " + getKeyName(currSetting->controls.rotate180));
    swapHold.setString("Swap Hold: " + getKeyName(currSetting->controls.swapHold));
}

// Updates slider values to match
// Author: Nathan
void Options::updateSliderValues() {
    arr.setValue(currSetting->handling.arr);
    das.setValue(currSetting->handling.das);
    dcd.setValue(currSetting->handling.dcd);
    sdf.setValue(currSetting->handling.sdf);
}

// Recenter a button pair that needs to be side by side
// Author: Nathan
void Options::recenterButtonPair(ToggleButton &b1, ToggleButton &b2) {
    unsigned int gapFromCenter = 8;
    float screenCenterX = screenWidth / 2.0;
    std::string b1Text = b1.getString();
    std::string b2Text = b2.getString();
    b1.setXPos(screenCenterX - gapFromCenter - (b1Text.length() * LCD.getCharWidth()));
    b2.setXPos(screenCenterX + gapFromCenter);
}

// Removes all option buttons
// Author: Nathan
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
