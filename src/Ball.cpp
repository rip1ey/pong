#include "Ball.h"

Ball::Ball(float x, float y)
{
  xpos = x;
  ypos = y;
  width = BALL_WIDTH;
  height = BALL_HEIGHT;
  speed = 300.0f;

  direction[0] = -1;
  direction[1] = 1;
  srand(time(NULL));

  rand_num = rand() % 2;
  velx = speed * direction[rand_num];
  vely = 0.0;
}

void Ball::MoveBall(float dt)
{
  xpos += velx * dt;
  ypos += vely * dt;
}
