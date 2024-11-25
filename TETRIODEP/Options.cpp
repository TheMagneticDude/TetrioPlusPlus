#include <chrono>

#include "Input.h"
#include "Options.h"
#include "Settings.h"

#include <iostream>

Options::Options(PlayerSettings &pSet)
    : left(0 + buttonoffset, "Move Left", BLUE, DARKBLUE), right(20 + buttonoffset, "Move Right", BLUE, DARKBLUE),
      softDrop(40 + buttonoffset, "Soft Drop", BLUE, DARKBLUE),
      hardDrop(60 + buttonoffset, "Hard Drop", BLUE, DARKBLUE),
      rotateCCW(80 + buttonoffset, "Rotate CCW", BLUE, DARKBLUE),
      rotateCW(100 + buttonoffset, "Rotate CW", BLUE, DARKBLUE),
      rotate180(120 + buttonoffset, "Rotate 180", BLUE, DARKBLUE),
      swapHold(140 + buttonoffset, "Swap Hold", BLUE, DARKBLUE), input(pSet) {
    playerSettings = pSet;
    control = playerSettings.controls;
}

void Options::update() {
    // update all button states
    left.updateButtonState();
    right.updateButtonState();
    softDrop.updateButtonState();
    hardDrop.updateButtonState();
    rotateCCW.updateButtonState();
    rotateCW.updateButtonState();
    rotate180.updateButtonState();
    swapHold.updateButtonState();

    // deboucnce
    if(left.onButtonClicked()){
        lastPress = std::chrono::high_resolution_clock::now();
    }
    
    auto currTime = std::chrono::high_resolution_clock::now();

    float debounceTime = 0.1;
    // only let run if enough time has passed
    if ((currTime - lastPress).count() > debounceTime) {

        if (left.getButtonTriggered()) {
            // gets first key pressed in the array read.
            // Will add support for multiple keys pressed at once eventually
            auto keys = input.scanKey();
            if (!keys.empty()) {
                int key = keys.front();
                std::cout << "KEYREAD: " << key << std::endl;
                input.setKey(PlayerInput::KeyAction::MoveLeft, key);
                left.setTriggered(false);
            }
        }

        if (right.getButtonTriggered()) {
            // gets first key pressed in the array read.
            // Will add support for multiple keys pressed at once eventually
            auto keys = input.scanKey();
            if (!keys.empty()) {
                int key = keys.front();
                std::cout << "KEYREAD: " << key << std::endl;
                input.setKey(PlayerInput::KeyAction::MoveRight, key);
                right.setTriggered(false);
            }
        }
    }
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
