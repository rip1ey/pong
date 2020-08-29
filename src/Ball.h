#ifndef BALL_H
#define BALL_H

#define BALL_HEIGHT 20
#define BALL_WIDTH 20

#include <stdlib.h>
#include <time.h>

class Ball
{
  public:
    int width;
    int height;
    float velx;
    float vely;
    int xpos;
    int ypos;

    Ball(int x, int y);
    void MoveBall(unsigned int dt);
  private:
    int direction[2];
    int rand_num;
};

#endif
