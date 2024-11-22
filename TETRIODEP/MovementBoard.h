#ifndef MOVEMENTBOARD.H
#define MOVEMENTBOARD .H
#include <ctime>
#include "../TETRIODEP/Key.h"
#include "../TETRIODEP/Grid.h"
class MovementBoard {
  private:
    Grid grid;

    //bounderies to confine the mino
    int xMin = 0;//tetris board coords
    int yMin = 0;
    
    int xMax;
    int yMax;
    
    //keys
    enum class keyState{
        CLICKED,//when first clicked
        PRESSED,//pressed
        INACTIVE//not being clicked
    };

    


    Key keyL;
    Key keyR;
    Key keyU;
    Key keyD;

//current moving piece's info
    int movingX;
    int movingY;
    Tetromino movingType;
    TetrominoOrientation movingOrientation;

    //moving piece timing vars
    
    //gravity tick in seconds
    float minoGravityTick = 1;
    time_t nextGravityTick; 
   

  public:
    int boardX;
    int boardY;
    MovementBoard(int x, int y);
    bool isTimeUp(time_t now, time_t &target, float tick);
    bool isBetween(int n, int min, int max);
    void draw();
    void update();
    void drawTetromino(int pos_x, int pos_y, Tetromino type, TetrominoOrientation orientation);
    int convertToGridCoordsX(int x);
    int convertToGridCoordsY(int y);


    void setMovingTetromino(int pos_x, int pos_y, Tetromino type, TetrominoOrientation orientation);


    void updateKeys();

};
#endif