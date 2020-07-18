#include "Paddle.h"

#define PADDLE_HEIGHT 100
#define PADDLE_WIDTH 10

Paddle::Paddle(int x, int y)
{
	xpos = x;
	ypos = y;
	height = PADDLE_HEIGHT;
	width = PADDLE_WIDTH;
}
