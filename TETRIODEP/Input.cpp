#include "Input.h"
#include "Settings.h"

#include <FEHLCD.h>
#include <chrono>
#include <iostream>

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif

#if __linux__ && !__ANDROID__
#include <X11/X.h>
#include <X11/Xlib.h>
#include <tigr.h>
#endif

TriggerKey::TriggerKey(int keyCode) : keyCode(keyCode), isPressed(false), isNewPress(false) {}

void TriggerKey::update() {
    bool currentlyIsPressed;

#ifdef _WIN32
    currentlyIsPressed = GetAsyncKeyState(keyCode);
#endif

#if __linux__ && !__ANDROID__
    // I'm sorry but it had to be done :)
    // The TigrInternal structure is placed directly after Tigr (Tigr* is at offset 0 in LCD)
    Tigr *internal = *reinterpret_cast<Tigr **>(&LCD) + 1;
    // The Display* is at offset 48 in TigrInternal
    uint8_t *disp_ptr = reinterpret_cast<uint8_t *>(internal) + 48;
    // Now we have it
    Display *display = *reinterpret_cast<Display **>(disp_ptr);

    char keymap[32];
    XQueryKeymap(display, keymap);
    int xKeyCode = XKeysymToKeycode(display, keyCode);
    currentlyIsPressed = keymap[xKeyCode / 8] & (1 << (xKeyCode % 8));
#endif

    if (currentlyIsPressed && !isPressed) {
        isPressed = true;
        isNewPress = true;
        holdStart = std::chrono::high_resolution_clock::now();
    } else if (!currentlyIsPressed && isPressed) {
        isPressed = false;
    }
}

bool TriggerKey::newPress() { return isNewPress; }

bool TriggerKey::pressed() { return isPressed; }

float TriggerKey::holdTime() {
    std::chrono::duration<float> duration = std::chrono::high_resolution_clock::now() - holdStart;
    return duration.count();
}

PlayerInput::PlayerInput(PlayerSettings &playerSettings)
    : handling(&playerSettings.handling), keyLeft(playerSettings.controls.moveLeft),
      keyRight(playerSettings.controls.moveRight), rotateCW(playerSettings.controls.rotateCW),
      rotateCCW(playerSettings.controls.rotateCCW), rotate180(playerSettings.controls.rotate180),
      softDrop(playerSettings.controls.softDrop), hardDrop(playerSettings.controls.hardDrop) {}

void PlayerInput::update() {
    keyLeft.update();
    keyRight.update();
    rotateCW.update();
    rotateCCW.update();
    rotate180.update();
    softDrop.update();
    hardDrop.update();
}
