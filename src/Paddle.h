#ifndef PADDLE_H
#define PADDLE_H

#define PADDLE_HEIGHT 100
#define PADDLE_WIDTH 10

class Paddle
{
	public:
		float x, y;
		int height, width;
		float xpos, ypos;
    float vely;     // paddle will only move in y direction

		Paddle(int x, int y);
    void MoveUp(unsigned int dt);
    void MoveDown(unsigned int dt);
};

#endif
