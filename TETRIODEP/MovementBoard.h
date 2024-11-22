#ifndef MOVEMENTBOARD.H
#define MOVEMENTBOARD .H

#include "../TETRIODEP/Grid.h"
class MovementBoard {
  private:
    Grid grid;

    bool keyL;
    bool keyR;
    bool keyU;
    bool keyD;

//current moving piece's info
    int movingX;
    int movingY;
    Tetromino movingType;
    TetrominoOrientation movingOrientation;
   

  public:
    int boardX;
    int boardY;
    MovementBoard(int x, int y);
    void draw();
    void update(bool L, bool R, bool U, bool D);
    void drawTetromino(int pos_x, int pos_y, Tetromino type, TetrominoOrientation orientation);
    int convertToGridCoordsX(int x);
    int convertToGridCoordsY(int y);


        void setMovingTetromino(int pos_x, int pos_y, Tetromino type, TetrominoOrientation orientation);

};
#endif