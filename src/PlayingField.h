#ifndef PLAYINGFIELD_H
#define PLAYINGFIELD_H

#include "Paddle.h"

class PlayingField
{
	public:
		Paddle *playerPaddle, *npcPaddle;
		static const int height = 720;
		static const int width = 1280;
		static const int divider = 8;

		PlayingField();
};

#endif
