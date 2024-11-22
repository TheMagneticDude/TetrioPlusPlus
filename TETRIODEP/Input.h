#pragma once

#include <chrono>

#include "Settings.h"

class TriggerKey {
  private:
    int keyCode;
    std::chrono::high_resolution_clock::time_point holdStart;
    bool isPressed;
    bool isNewPress;
    bool useDAS;

  public:
    TriggerKey(int keyCode, bool useDAS);
    void update();
    bool newPress();
    bool pressed();
    // Returns the time in seconds
    float holdTime();
    // Simulate a new press and reset the hold timer (used for e.g. DAS)
    void resetHold();
};

class PlayerInput {
  private:
    PlayerHandling *handling;

    bool repeatingLeft;
    bool repeatingRight;

    void handleDAS(bool &isRepeating, TriggerKey &key);

  public:
    // It's in FEH best practices to have all fields be private, but in this case it makes sense for a user of the
    // PlayerInput class to have full access of these, as PlayerInput is a thin wrapper for convenience and organization
    TriggerKey keyLeft;
    TriggerKey keyRight;
    TriggerKey rotateCW;
    TriggerKey rotateCCW;
    TriggerKey rotate180;
    TriggerKey softDrop;
    TriggerKey hardDrop;
    TriggerKey swapHold;

    PlayerInput(PlayerSettings &playerSettings);
    void update();
};
