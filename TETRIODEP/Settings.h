#pragma once

struct PlayerHandling {
    // Auto Repeat Rate
    float arr;
    // Delayed Auto Shift
    float das;
    // DAS Cut Delay
    float dcd;
    // Soft Drop Factor
    float sdf;
};

struct PlayerControls {
    int moveLeft;
    int moveRight;
    int softDrop;
    int hardDrop;
    int rotateCCW;
    int rotateCW;
    int rotate180;
    int swapHold;
};

struct PlayerSettings {
    PlayerHandling handling;
    PlayerControls controls;
};

struct Settings {
    PlayerSettings p1Settings;
    PlayerSettings p2Settings;
};
