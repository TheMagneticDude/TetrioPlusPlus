#ifndef MOVEMENTBOARD.H
#define MOVEMENTBOARD .H

#include "../TETRIODEP/Grid.h"
class MovementBoard {
  private:
    Grid grid;

    bool keyL;
    bool keyR;

//current moving piece's coords
    int movingX;
    int movingY;
   

  public:
    int boardX;
    int boardY;
    MovementBoard(int x, int y);
    void draw();
    void update(bool L, bool R);
    void drawTetromino(int pos_x, int pos_y, Tetromino type, TetrominoOrientation orientation);
    int convertToGridCoordsX(int x);
    int convertToGridCoordsY(int y);


        void drawMovingTetromino(int pos_x, int pos_y, Tetromino type, TetrominoOrientation orientation);

};
#endif