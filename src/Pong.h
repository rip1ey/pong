#ifndef PONG_H
#define PONG_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "Paddle.h"
#include "PlayingField.h"

class Pong
{
  public:
    TTF_Font *font;
    SDL_Window *window;
    SDL_Renderer *renderer;
    PlayingField *Field;
    int play_has_started;
    SDL_Surface *P1ScoreSurf, *P2ScoreSurf;

    int Init();
    int HaveWinner();
    void ResetGame();
    void RenderScores();
    void DrawPlayingField(SDL_Rect& lineRect);
    void DrawPaddles(SDL_Rect& player, SDL_Rect& npc);
    void DrawBall(SDL_Rect& ball);
};

#endif
