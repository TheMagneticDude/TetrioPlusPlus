#pragma once

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#define KEY_A VK_A
#define KEY_B VK_B
#define KEY_C VK_C
#define KEY_D VK_D
#define KEY_E VK_E
#define KEY_F VK_F
#define KEY_G VK_G
#define KEY_H VK_H
#define KEY_I VK_I
#define KEY_J VK_J
#define KEY_K VK_K
#define KEY_L VK_L
#define KEY_M VK_M
#define KEY_N VK_N
#define KEY_O VK_O
#define KEY_P VK_P
#define KEY_Q VK_Q
#define KEY_R VK_R
#define KEY_S VK_S
#define KEY_T VK_T
#define KEY_U VK_U
#define KEY_V VK_V
#define KEY_W VK_W
#define KEY_X VK_X
#define KEY_Y VK_Y
#define KEY_Z VK_Z

#define KEY_LEFT VK_LEFT
#define KEY_RIGHT VK_RIGHT
#define KEY_UP VK_UP
#define KEY_DOWN VK_DOWN

#define KEY_COMMA VK_OEM_COMMA

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

struct PlayerSettings {
    PlayerHandling handling;
    PlayerControls controls;
};

struct Settings {
    PlayerSettings p1Settings;
    PlayerSettings p2Settings;
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
            .hardDrop = KEY_F,
            .rotateCCW = KEY_X,
            .rotateCW = KEY_C,
            .rotate180 = KEY_Z,
            .swapHold = KEY_F,
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
