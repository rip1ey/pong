#include "Paddle.h"

Paddle::Paddle(int x, int y)
{
	xpos = x;
	ypos = y;
	height = PADDLE_HEIGHT;
	width = PADDLE_WIDTH;
  vely = .01f;
}

void Paddle::MoveUp(unsigned int dt)
{
  ypos += -vely * dt;
}

void Paddle::MoveDown(unsigned int dt)
{
  ypos += vely * dt;
}
