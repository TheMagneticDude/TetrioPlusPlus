#pragma once

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#define KEY_A 0x41
#define KEY_B 0x42
#define KEY_C 0x43
#define KEY_D 0x44
#define KEY_E 0x45
#define KEY_F 0x46
#define KEY_G 0x47
#define KEY_H 0x48
#define KEY_I 0x49
#define KEY_J 0x4A
#define KEY_K 0x4B
#define KEY_L 0x4C
#define KEY_M 0x4D
#define KEY_N 0x4E
#define KEY_O 0x4F
#define KEY_P 0x50
#define KEY_Q 0x51
#define KEY_R 0x52
#define KEY_S 0x53
#define KEY_T 0x54
#define KEY_U 0x55
#define KEY_V 0x56
#define KEY_W 0x57
#define KEY_X 0x58
#define KEY_Y 0x59
#define KEY_Z 0x5A

#define KEY_LEFT VK_LEFT
#define KEY_RIGHT VK_RIGHT
#define KEY_UP VK_UP
#define KEY_DOWN VK_DOWN

#define KEY_COMMA VK_OEM_COMMA

#define KEY_SPACE VK_SPACE
#define KEY_SHIFT VK_SHIFT
#define KEY_LEFT_ALT VK_LMENU
#define KEY_RIGHT_ALT VK_RMENU



#endif

#if __linux__ && !__ANDROID__
#include <X11/keysym.h>

#define KEY_A XK_a
#define KEY_B XK_b
#define KEY_C XK_c
#define KEY_D XK_d
#define KEY_E XK_e
#define KEY_F XK_f
#define KEY_G XK_g
#define KEY_H XK_h
#define KEY_I XK_i
#define KEY_J XK_j
#define KEY_K XK_k
#define KEY_L XK_l
#define KEY_M XK_m
#define KEY_N XK_n
#define KEY_O XK_o
#define KEY_P XK_p
#define KEY_Q XK_q
#define KEY_R XK_r
#define KEY_S XK_s
#define KEY_T XK_t
#define KEY_U XK_u
#define KEY_V XK_v
#define KEY_W XK_w
#define KEY_X XK_x
#define KEY_Y XK_y
#define KEY_Z XK_z

#define KEY_LEFT XK_Left
#define KEY_RIGHT XK_Right
#define KEY_UP XK_Up
#define KEY_DOWN XK_Down

#define KEY_COMMA XK_comma

#define KEY_SPACE XK_space
#define KEY_SHIFT XK_Shift_L
#define KEY_LEFT_ALT XK_Alt_L
#define KEY_RIGHT_ALT XK_Alt_R

#endif

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

struct PlayerStats{
    int linesCleared;
    int gamesWon;
};

struct PlayerSettings {
    PlayerHandling handling;
    PlayerControls controls;
};

struct Settings {
    PlayerSettings p1Settings;
    PlayerSettings p2Settings;
};

struct Statistics{
    PlayerStats p1Stats;
    PlayerStats p2Stats;
};
inline constexpr Statistics statistics = Statistics {
    .p1Stats = {
        .linesCleared = 0,
        .gamesWon = 0
    },

    .p2Stats = {
        .linesCleared = 0,
        .gamesWon = 0
    }
};

inline constexpr Settings defaultSettings = Settings {
    .p1Settings = {
        .handling = {
            .arr = 0.033,
            .das = 0.167,
            .dcd = 0.017,
            .sdf = 6.0,
        },
        .controls = {
            .moveLeft = KEY_F,
            .moveRight = KEY_H,
            .softDrop = KEY_G,
            .hardDrop = KEY_SPACE,
            .rotateCCW = KEY_X,
            .rotateCW = KEY_C,
            .rotate180 = KEY_Z,
            .swapHold = KEY_SHIFT,
        }
    },
    .p2Settings = {
        .handling = {
            .arr = 0.033,
            .das = 0.167,
            .dcd = 0.017,
            .sdf = 6.0,
        },
        .controls = {
            .moveLeft = KEY_LEFT,
            .moveRight = KEY_RIGHT,
            .softDrop = KEY_DOWN,
            .hardDrop = KEY_RIGHT_ALT,
            .rotateCCW = KEY_COMMA,
            .rotateCW = KEY_UP,
            .rotate180 = KEY_M,
            .swapHold = KEY_N,
        }
    }
};


