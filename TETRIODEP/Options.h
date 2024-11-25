#pragma once

#include "Grid.h"
#include "Input.h"
#include "Settings.h"
#include "ToggleButton.h"

class Options {
  private:
    int buttonoffset = 30;
    PlayerSettings playerSettings;
    PlayerControls control;
    PlayerInput input;

    ToggleButton left;
    ToggleButton right;
    ToggleButton softDrop;
    ToggleButton hardDrop;
    ToggleButton rotateCCW;
    ToggleButton rotateCW;
    ToggleButton rotate180;
    ToggleButton swapHold;

    std::chrono::high_resolution_clock::time_point lastPress;

  public:
    Options(PlayerSettings &pSet);
    void update();
    void setKey(TriggerKey &key);
    void remove();
};
