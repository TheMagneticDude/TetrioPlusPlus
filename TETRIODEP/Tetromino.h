#pragma once

#include <cstdint>

enum class Tetromino : uint8_t {
    E, // Empty, there is nothing here
    I, // Straight line
    J, // Inverse L
    L, // Normal L
    O, // Square
    S, // Right Snake
    T, // T shape
    Z, // Left Snake
    G, // Garbage
};

enum class TetrominoOrientation : uint8_t {
    H, // 0 = spawn state (horizontal)
    R, // R = state resulting from a clockwise rotation ("right") from spawn
    L, // L = state resulting from a counter-clockwise ("left") rotation from spawn
    U  // 2 = state resulting from 2 successive rotations in either direction from spawn.
};
