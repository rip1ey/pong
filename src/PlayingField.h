#ifndef PLAYINGFIELD_H
#define PLAYINGFIELD_H

#include "Paddle.h"
#include "Ball.h"

class PlayingField
{
	public:
		Paddle *playerPaddle, *npcPaddle;
    Ball *ball;

		static const int height = 720;
		static const int width = 1280;
		static const int divider = 8;

		PlayingField();
    void MovePaddleUp(Paddle& paddle, unsigned int dt);
    void MovePaddleDown(Paddle& paddle, unsigned int dt);
};

#endif
