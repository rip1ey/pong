#include "Pong.h"

#define DEBUG_PONG

// create a method to draw the playing field
// create a method to draw the paddles
int Pong::Init()
{
	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) != 0)
	{
		SDL_Log("Failed to initialize SDL: %s\n", SDL_GetError());
		return -1;
	}

	this->Field = new PlayingField();
	PlayingField *field = this->Field;
	this->window = SDL_CreateWindow("Pong",
																	SDL_WINDOWPOS_CENTERED,
																	SDL_WINDOWPOS_CENTERED,
																	field->width,
																	field->height,
																	0);

	if(this->window == NULL)
	{
		SDL_Log("Failed to create SDL window: %s\n", SDL_GetError());
		SDL_Quit();
		return -1;
	}

	this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED);
	if(this->renderer == NULL)
	{
		SDL_Log("Failed to create SDL renderer: %s\n", SDL_GetError());
		SDL_DestroyWindow(this->window);
		SDL_Quit();
		return -1;
	}

#ifdef DEBUG_PONG
	cout << "Successfully created a window and a renderer" << endl;
#endif

	return 0;
}

/*
 *	The playing field should be black
 *	with a white line / rectangle in the middle
 *
 *	The field should take up the whole space, whereas
 *	the line should divide the playing area
 */
void Pong::DrawPlayingField(SDL_Rect& fieldRect, SDL_Rect& lineRect)
{
	int DividerLoc = this->Field->width / 2;

	fieldRect.x = 0;
	fieldRect.y = 0;
	fieldRect.w = this->Field->width;
	fieldRect.h = this->Field->height;

	lineRect.x = DividerLoc - (this->Field->divider / 2);;
	lineRect.w = this->Field->divider;
	lineRect.y = 0;
	lineRect.h = this->Field->height;

	// Set the draw color to black and draw the field
	SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawRect(this->renderer, &fieldRect);
	SDL_RenderFillRect(this->renderer, &fieldRect);

	// Set the draw color to white and draw the dividing line
	SDL_SetRenderDrawColor(this->renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawRect(this->renderer, &lineRect);
	SDL_RenderFillRect(this->renderer, &lineRect);

#ifdef DEBUG_PONG
	cout << "Field width: " << this->Field->width << endl;
	cout << "Field height: " << this->Field->height << endl;
	cout << "Divider location: " << DividerLoc << endl;
	cout << "Field x, y, width, and height: " << fieldRect.x << ", " << fieldRect.y << ", " << fieldRect.w << ", " << fieldRect.h << endl;
	cout << "Divider x, y, width, and height: " << lineRect.x << ", " << lineRect.y << ", " << lineRect.w << ", " << lineRect.h << endl;
#endif

	SDL_RenderPresent(this->renderer);
}

int main(int argc, char *argv[])
{
	SDL_Event event;
	bool quit = false;
	SDL_Rect fieldRect, divideRect, playerRect, npcRect;
	Pong Pong;

	if(Pong.Init() < 0)
	{
		cout << "An error occurred with starting Pong. Closing..." << endl;
		return -1;
	}

	Pong.DrawPlayingField(fieldRect, divideRect);

	while(!quit)
	{
		while(SDL_PollEvent(&event))
		{
			if(event.type == SDL_QUIT)
			{
				quit = true;
			}
			if(event.type == SDL_KEYDOWN)
			{
				quit = true;
			}
			if(event.type == SDL_MOUSEBUTTONDOWN)
			{
				quit = true;
			}
		}
	}
}
