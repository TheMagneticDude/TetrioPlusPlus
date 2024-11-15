#include <FEHLCD.h>
#include <FEHRandom.h>
#include <cstdint>
#include <optional>
#include <vector>
#include <Tetromino.h>
#include <Grid.h>

#define SCALE 6


Grid::Grid(int width, int height) : width(width), height(height), data(width * height) {}


void Grid::draw(int pos_x, int pos_y) {
        for (int x = 0; x < width; x++) {
            for (int y = 0; y < height; y++) {
                auto mino = data[y * 10 + x];
                unsigned int colors[] = {BLACK, AQUA, BLUE, ORANGE, YELLOW, GREEN, PURPLE, RED};
                unsigned int color = colors[static_cast<size_t>(mino)];
                LCD.SetFontColor(color);
                LCD.FillRectangle(pos_x + x * SCALE, pos_y + y * SCALE, SCALE, SCALE);
            }
        }
    }
    




