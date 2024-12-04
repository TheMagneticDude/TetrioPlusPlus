#pragma once

#include "Grid.h"
#include "Input.h"
#include "Settings.h"
#include "Slider.h"
#include "Switch.h"
#include "ToggleButton.h"
#include "Button.h"

class Options {
  private:
    const unsigned int screenWidth = 320;
    const unsigned int screenHeight = 240;

    Switch togglePlayer;
    bool switchToggled;
    bool wasToggled;

    Slider arr;
    Slider das;
    Slider dcd;
    Slider sdf;

    int buttonoffset = 80;
    Settings *settings;

    PlayerInput p1Input;
    PlayerInput p2Input;
    PlayerInput *currentPlayerInput;
    PlayerSettings *currSetting;

    ToggleButton left;
    ToggleButton right;
    ToggleButton softDrop;
    ToggleButton hardDrop;
    ToggleButton rotateCCW;
    ToggleButton rotateCW;
    ToggleButton rotate180;
    ToggleButton swapHold;

    Button preset;

    enum class buttons { left, right, softDrop, hardDrop, rotateCCW, rotateCW, rotate180, swapHold, none };

    buttons currActive = buttons::none;

    std::chrono::high_resolution_clock::time_point lastPress;

    // map of all the key names bc windows doesent give an easy way to do it to my knowledge
    std::map<int, std::string> keyNameMap = {{0x10, "SHIFT"},
                                             {0x20, "SPACEBAR"},
                                             {0x21, "PAGE UP"},
                                             {0x22, "PAGE DOWN"},
                                             {0x23, "END"},
                                             {0x24, "HOME"},
                                             {0x25, "LEFT ARROW"},
                                             {0x26, "UP ARROW"},
                                             {0x27, "RIGHT ARROW"},
                                             {0x28, "DOWN ARROW"},
                                             {0x29, "SELECT"},
                                             {0x2A, "PRINT"},
                                             {0x2B, "EXECUTE"},
                                             {0x2C, "PRINT SCREEN"},
                                             {0x2D, "INS"},
                                             {0x2E, "DEL"},
                                             {0x2F, "HELP"},
                                             {0x30, "0"},
                                             {0x31, "1"},
                                             {0x32, "2"},
                                             {0x33, "3"},
                                             {0x34, "4"},
                                             {0x35, "5"},
                                             {0x36, "6"},
                                             {0x37, "7"},
                                             {0x38, "8"},
                                             {0x39, "9"},
                                             {0x41, "A"},
                                             {0x42, "B"},
                                             {0x43, "C"},
                                             {0x44, "D"},
                                             {0x45, "E"},
                                             {0x46, "F"},
                                             {0x47, "G"},
                                             {0x48, "H"},
                                             {0x49, "I"},
                                             {0x4A, "J"},
                                             {0x4B, "K"},
                                             {0x4C, "L"},
                                             {0x4D, "M"},
                                             {0x4E, "N"},
                                             {0x4F, "O"},
                                             {0x50, "P"},
                                             {0x51, "Q"},
                                             {0x52, "R"},
                                             {0x53, "S"},
                                             {0x54, "T"},
                                             {0x55, "U"},
                                             {0x56, "V"},
                                             {0x57, "W"},
                                             {0x58, "X"},
                                             {0x59, "Y"},
                                             {0x5A, "Z"},
                                             {0x5B, "Left Windows"},
                                             {0x5C, "Right Windows"},
                                             {0x5D, "Applications"},
                                             {0x5F, "Sleep"},
                                             {0x60, "NUMPAD0"},
                                             {0x61, "NUMPAD1"},
                                             {0x62, "NUMPAD2"},
                                             {0x63, "NUMPAD3"},
                                             {0x64, "NUMPAD4"},
                                             {0x65, "NUMPAD5"},
                                             {0x66, "NUMPAD6"},
                                             {0x67, "NUMPAD7"},
                                             {0x68, "NUMPAD8"},
                                             {0x69, "NUMPAD9"},
                                             {0x6A, "NUMPAD*"},
                                             {0x6B, "NUMPAD+"},
                                             {0x6C, "Separator"},
                                             {0x6D, "NUMPAD-"},
                                             {0x6E, "NUMPAD."},
                                             {0x6F, "NUMPAD/"},
                                             {0x70, "F1"},
                                             {0x71, "F2"},
                                             {0x72, "F3"},
                                             {0x73, "F4"},
                                             {0x74, "F5"},
                                             {0x75, "F6"},
                                             {0x76, "F7"},
                                             {0x77, "F8"},
                                             {0x78, "F9"},
                                             {0x79, "F10"},
                                             {0x7A, "F11"},
                                             {0x7B, "F12"},
                                             {0x7C, "F13"},
                                             {0x7D, "F14"},
                                             {0x7E, "F15"},
                                             {0x7F, "F16"},
                                             {0x80, "F17"},
                                             {0x81, "F18"},
                                             {0x82, "F19"},
                                             {0x83, "F20"},
                                             {0x84, "F21"},
                                             {0x85, "F22"},
                                             {0x86, "F23"},
                                             {0x87, "F24"},
                                             {0x90, "NUM LOCK"},
                                             {0x91, "SCROLL LOCK"},
                                             {0xA0, "Left SHIFT"},
                                             {0xA1, "Right SHIFT"},
                                             {0xA2, "Left CONTROL"},
                                             {0xA3, "Right CONTROL"},
                                             {0xA4, "Left ALT"},
                                             {0xA5, "Right ALT"},
                                             {0xA6, "Browser Back"},
                                             {0xA7, "Browser Forward"},
                                             {0xA8, "Browser Refresh"},
                                             {0xA9, "Browser Stop"},
                                             {0xAA, "Browser Search"},
                                             {0xAB, "Browser Favorites"},
                                             {0xAC, "Browser Start/Home"},
                                             {0xAD, "Volume Mute"},
                                             {0xAE, "Volume Down"},
                                             {0xAF, "Volume Up"},
                                             {0xB0, "Next Track"},
                                             {0xB1, "Previous Track"},
                                             {0xB2, "Stop Media"},
                                             {0xB3, "Play/Pause Media"},
                                             {0xB4, "Launch Mail"},
                                             {0xB5, "Launch Media Select"},
                                             {0xB6, "Launch App 1"},
                                             {0xB7, "Launch App 2"},
                                             {0xBA, ";"},
                                             {0xBB, "OEM Plus"},
                                             {0xBC, "OEM Comma"},
                                             {0xBD, "OEM Minus"},
                                             {0xBE, "OEM Period"},
                                             {0xBF, "OEM 2"},
                                             {0xC0, "OEM 3"},
                                             {0xDB, "OEM 4"},
                                             {0xDC, "OEM 5"},
                                             {0xDD, "OEM 6"},
                                             {0xDE, "OEM 7"},
                                             {0xDF, "OEM 8"},
                                             {0xE2, "OEM 102"},
                                             {0xE5, "IME Process"},
                                             {0xE7, "Packet"},
                                             {0xF6, "Attn"},
                                             {0xF7, "CrSel"},
                                             {0xF8, "ExSel"},
                                             {0xF9, "Erase EOF"},
                                             {0xFA, "Play"},
                                             {0xFB, "Zoom"},
                                             {0xFC, "Noname"},
                                             {0xFD, "PA1"},
                                             {0xFE, "OEM Clear"},
                                             {-1, "UNKNOWN"}};

  public:
    Options(Settings &set);
    void update();
    void untoggleOthers(ToggleButton &b);
    bool otherButtonToggled(ToggleButton &b);
    void getCurrentButton();
    void handleButtonToggle(ToggleButton &b);
    bool anyButtonToggled();
    void remove();
    std::string getKeyName(int key);

    void updateButtonNames();
    void updateSliderValues();

    void recenterButtonPair(ToggleButton &b1, ToggleButton &b2);
};
