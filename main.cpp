#include <FEHLCD.h>
#include <FEHRandom.h>
#include <cstdint>
#include <optional>
#include <vector>

#include<Tetromino.h>
#include<Grid.h>
#include<TetrisBoard.h>


int main() {
    TetrisBoard board;

    while (1) {
        LCD.Clear();
        board.draw(100, 100);
        LCD.Update();
    }

    return 0;
}
