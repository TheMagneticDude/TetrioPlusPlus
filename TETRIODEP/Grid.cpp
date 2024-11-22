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
            std::cout << color << std::endl;
            if (color != BLACK) {
                drawMino(pos_x + x * SCALE, pos_y + y * SCALE, color);
            }

            // LCD.SetFontColor(color);
            // LCD.FillRectangle(pos_x + x * SCALE, pos_y + y * SCALE, SCALE, SCALE);
        }
    }
}

void Grid::addMino(Tetromino tetromino, int x, int y) {
    // assigns color blue for now
    auto mino = static_cast<Tetromino>(3);
    std::cout << "x:" << x << std::endl;
    std::cout << "y:" << y << std::endl;
    data[y * width + x] = mino;
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
void Grid::removeMino(int pos_x, int pos_y) {
    LCD.SetFontColor(backgroundColor);
    LCD.FillRectangle(pos_x, pos_y - SCALE, SCALE, SCALE);
}
