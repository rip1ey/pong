#ifndef PADDLE_H
#define PADDLE_H

class Paddle
{
	public:
		int x, y;
		int height, width;
		int xpos, ypos;
		static const int speed = 5;

		Paddle(int x, int y);
};

#endif
