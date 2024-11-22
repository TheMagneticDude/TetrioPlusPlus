#include <vector>
#include <iostream>

#include "Grid.h"
#include "Tetromino.h"
#include <FEHLCD.h>
#include <FEHRandom.h>

Grid::Grid(int width, int height) : width(width), height(height), data(width * height, Tetromino::E) {}

void Grid::draw(int pos_x, int pos_y) {
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            auto mino = data[y * width + x];
            unsigned int colors[] = {BLACK, AQUA, BLUE, ORANGE, YELLOW, GREEN, PURPLE, RED};
            unsigned int color = colors[static_cast<size_t>(mino)];
            // draws mino with shading
            if (color != BLACK) {
                drawMino(pos_x + x * SCALE, height * SCALE - pos_y + y * SCALE, color);
            }
        }
    }
}

Tetromino Grid::getAtPos(int x, int y) {
    return data[y * width + x];
}

void Grid::addMino(Tetromino tetromino, int x, int y) {
    auto mino = tetromino;
    data[y * width + x] = mino;
}

void Grid::removeMino(int pos_x, int pos_y) {
   auto mino = Tetromino::E;
    data[pos_y * width + pos_x] = mino;
}

// draws a mino with the bottom left corner at pos_x and pos_y
void Grid::drawMino(int pos_x, int pos_y, int color) {
    LCD.SetFontColor(color);
    LCD.FillRectangle(pos_x, pos_y - SCALE, SCALE, SCALE);

    // Mino outline
    LCD.SetFontColor(color - 0x00009f);
    LCD.DrawRectangle(pos_x, pos_y - SCALE, SCALE, SCALE);

    // Mino shading (brighter on left and top) according to wiki
    LCD.SetFontColor(color + 0x001f00);
    // top line
    LCD.DrawLine(pos_x, pos_y - SCALE, pos_x + SCALE - 1, pos_y - SCALE);
    // left line
    LCD.DrawLine(pos_x, pos_y - SCALE, pos_x, pos_y);
}

