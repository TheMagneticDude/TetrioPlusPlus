#include "../TETRIODEP/Grid.h"
#include "../TETRIODEP/Tetromino.h"
#include <FEHLCD.h>
#include <FEHRandom.h>
#include <cstdint>
#include <iostream>
#include <optional>
#include <vector>

Grid::Grid(int width, int height) : width(width), height(height), data(width * height) {}

void Grid::draw(int pos_x, int pos_y) {
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            auto mino = data[y * width + x];
            unsigned int colors[] = {BLACK, AQUA, BLUE, ORANGE, YELLOW, GREEN, PURPLE, RED};
            unsigned int color = colors[static_cast<size_t>(mino)];
            // draws mino with shading
            if (color != BLACK) {
                drawMino(x, y, color);
            }

            // LCD.SetFontColor(color);
            // LCD.FillRectangle(pos_x + x * SCALE, pos_y + y * SCALE, SCALE, SCALE);
        }
    }
}

void addMino(Tetromino mino) {}

// draws boarder around grid
void Grid::drawBoarder(int pos_x, int pos_y) {
    // top bottom boarders
    LCD.SetFontColor(WHITE);
    // top boarder
    LCD.FillRectangle(pos_x - SCALE, pos_y - SCALE, SCALE * (width + 2), SCALE);
    // bottom boarder
    LCD.FillRectangle(pos_x - SCALE, pos_y + SCALE * height, SCALE * (width + 2), SCALE);

    // left and right boarders
    // Left boarder
    LCD.FillRectangle(pos_x - SCALE, pos_y - SCALE, SCALE, SCALE * (height + 2));
    // // bottom boarder
    LCD.FillRectangle(pos_x + SCALE * width, pos_y - SCALE, SCALE, SCALE * (height + 2));
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
