#include <FEHLCD.h>
#include <FEHRandom.h>
#include <cstdint>
#include <optional>
#include <vector>

#define SCALE 6

enum class Tetromino : uint8_t {
    // Empty, there is nothing here
    E,
    I,
    J,
    L,
    O,
    S,
    T,
    Z
};

class Grid {
  private:
    int width;
    int height;

  public:
    std::vector<Tetromino> data;

    Grid(int width, int height) : width(width), height(height), data(width * height) {}

    void draw(int pos_x, int pos_y) {
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
};

class TetrisBoard {
    Grid grid;
    // std::optional<Grid *> mino;
  public:
    TetrisBoard() : grid(10, 20) {
        for (int x = 0; x < 10; x++) {
            for (int y = 0; y < 20; y++) {
                auto mino = static_cast<Tetromino>(Random.RandInt() % 7);
                grid.data[y * 10 + x] = mino;
            }
        }
    }
    void draw(int pos_x, int pos_y) { grid.draw(pos_x, pos_y); }
};

int main() {
    TetrisBoard board;

    while (1) {
        LCD.Clear();
        board.draw(100, 100);
        LCD.Update();
    }

    return 0;
}
