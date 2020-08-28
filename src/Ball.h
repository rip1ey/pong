#ifndef BALL_H
#define BALL_H

#define BALL_HEIGHT 20
#define BALL_WIDTH 20

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
};

#endif
