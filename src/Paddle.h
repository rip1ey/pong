#ifndef PADDLE_H
#define PADDLE_H

#define PADDLE_HEIGHT 100
#define PADDLE_WIDTH 10

#include <iostream>
using namespace std;

class Paddle
{
  public:
    float x, y;
    int height, width;
    float xpos, ypos;
    float vely;     // paddle will only move in y direction

    Paddle(float x, float y);
    void MoveUp(float dt);
    void MoveDown(float dt);
};

#endif
