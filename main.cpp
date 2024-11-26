#include "TETRIODEP/Menu.h"
#include "TETRIODEP/Options.h"
#include "TETRIODEP/Switch.h"
#include "TETRIODEP/TetrisBoard.h"
#include <FEHLCD.h>
#include <FEHRandom.h>

int main() {

    Menu mainMenu = Menu();

    while (1) {
        LCD.Clear();
        mainMenu.run();
        LCD.Update();
    }

    return 0;
}
