#ifndef GRID_H
#define GRID_H
#include<Tetromino.h>
#include<vector>

class Grid {
  private:
    int width;
    int height;

  public:
    std::vector<Tetromino> data;

    Grid(int width, int height);

    void draw(int pos_x, int pos_y) {}
};
extern Grid grid; 
#endif



