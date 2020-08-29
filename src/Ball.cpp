#include "Ball.h"

Ball::Ball(int x, int y)
{
  xpos = x;
  ypos = y;
  width = BALL_WIDTH;
  height = BALL_HEIGHT;

  direction[0] = -1;
  direction[1] = 1;
  srand(time(NULL));

  rand_num = rand() % 2;
  velx = 1.0f * direction[rand_num];
  vely = 0;
}

void Ball::MoveBall(unsigned int dt)
{
  xpos += velx * dt;
  ypos += vely * dt;
}
