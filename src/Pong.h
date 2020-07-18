#ifndef PONG_H
#define PONG_H

#include <iostream>
#include <SDL2/SDL.h>

#include "Paddle.h"
#include "PlayingField.h"
using namespace std;

class Pong
{
	public:
		SDL_Window *window;
		SDL_Renderer *renderer;
		PlayingField *Field;

		int Init();
		void DrawPlayingField(SDL_Rect& fieldRect, SDL_Rect& lineRect);
};

#endif
