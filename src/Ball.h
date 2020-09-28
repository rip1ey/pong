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
    float xpos;
    float ypos;
    float speed;

    Ball(float x, float y);
    void MoveBall(float dt);
  private:
    int direction[2];
    int rand_num;
};

#endif
