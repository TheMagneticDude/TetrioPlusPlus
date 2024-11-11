#include "FEHLCD.h"

int main()
{
    LCD.WriteLine("Hello World!");
    while (1) {
        LCD.Update();
        // Never end
        //test for github
    }
    return 0;
}