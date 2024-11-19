#include <cstdint>
#ifndef TETROMINO_H
#define TETROMINO_H


enum class Tetromino : uint8_t {
    E,// Empty, there is nothing here
    I,//Straight line 
    J,//Inverse L
    L,//Normal L
    O,//Square
    S,//Right Snake
    T,//T shape
    Z//Left Snake
};
#endif