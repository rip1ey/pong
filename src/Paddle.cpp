#include "Paddle.h"

Paddle::Paddle(float x, float y)
{
  xpos = x;
  ypos = y;
  height = PADDLE_HEIGHT;
  width = PADDLE_WIDTH;
  vely = 600.0f;
}

void Paddle::MoveUp(float dt)
{
  ypos += -vely * dt;
}

void Paddle::MoveDown(float dt)
{
  ypos += vely * dt;
}
