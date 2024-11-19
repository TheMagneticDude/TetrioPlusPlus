#include "../TETRIODEP/Grid.h"
#include "../TETRIODEP/Tetromino.h"
#include <FEHLCD.h>
#include <FEHRandom.h>
#include <cstdint>
#include <optional>
#include <vector>
#include <iostream>

#define SCALE 6

Grid::Grid(int width, int height) : width(width), height(height), data(width * height) {}

void Grid::draw(int pos_x, int pos_y) {
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            auto mino = data[y * width + x];
            unsigned int colors[] = {BLACK, AQUA, BLUE, ORANGE, YELLOW, GREEN, PURPLE, RED};
            unsigned int color = colors[static_cast<size_t>(mino)];
            LCD.SetFontColor(color);
            LCD.FillRectangle(pos_x + x * SCALE, pos_y + y * SCALE, SCALE, SCALE);
        }
    }
}
//draws boarder around grid
void Grid::drawBoarder(int pos_x, int pos_y) {
    // top bottom boarders
    LCD.SetFontColor(WHITE);
        // top boarder
        LCD.FillRectangle(pos_x - SCALE, pos_y - SCALE, SCALE*(width+2), SCALE);
        // bottom boarder
        LCD.FillRectangle(pos_x - SCALE, pos_y + SCALE*height, SCALE*(width+2), SCALE);
    
    // left and right boarders
        //Left boarder
        LCD.FillRectangle(pos_x - SCALE, pos_y - SCALE, SCALE, SCALE*(height+2));
        // // bottom boarder
        LCD.FillRectangle(pos_x + SCALE*width, pos_y - SCALE, SCALE, SCALE*(height+2));
}

//draws a mino with the top left corner at pos_x and pos_y
void Grid::drawMino(int pos_x, int pos_y, int color){
    LCD.SetFontColor(color);
    LCD.FillRectangle(pos_x * SCALE, pos_y * SCALE, SCALE, SCALE);
}
