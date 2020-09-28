#include "Pong.h"

//#define DEBUG_PONG

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
                                  SDL_WINDOW_ALLOW_HIGHDPI);

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

  int ret_num = SDL_RenderSetLogicalSize(renderer, field->width, field->height);
#ifdef DEBUG_PONG
  cout << ret_num << endl;
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
void Pong::DrawPlayingField(SDL_Rect& lineRect)
{
  int DividerLoc = this->Field->width / 2;

  // ensure that the renderer is cleared, and the background is black
  SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
  SDL_RenderClear(this->renderer);

  lineRect.x = DividerLoc - (this->Field->divider / 2);;
  lineRect.w = this->Field->divider;
  lineRect.y = 0;
  lineRect.h = this->Field->height;

  // Set the draw color to white and draw the dividing line
  SDL_SetRenderDrawColor(this->renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
  SDL_RenderFillRect(this->renderer, &lineRect);

#ifdef DEBUG_PONG
  cout << "Field width: " << this->Field->width << endl;
  cout << "Field height: " << this->Field->height << endl;
  cout << "Divider location: " << DividerLoc << endl;
  cout << "Divider x, y, width, and height: " << lineRect.x << ", " << lineRect.y << ", " << lineRect.w << ", " << lineRect.h << endl;
#endif
}

void Pong::DrawPaddles(SDL_Rect& player, SDL_Rect& npc)
{
  Paddle *PlayerPaddle = this->Field->playerPaddle;
  player.x = PlayerPaddle->xpos;
  player.y = PlayerPaddle->ypos;
  player.w = PlayerPaddle->width;
  player.h = PlayerPaddle->height;

  Paddle *NPCPaddle = this->Field->npcPaddle;
  npc.x = NPCPaddle->xpos;
  npc.y = NPCPaddle->ypos;
  npc.w = NPCPaddle->width;
  npc.h = NPCPaddle->height;

  // ensure the draw color is white
  SDL_SetRenderDrawColor(this->renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
  SDL_RenderFillRect(this->renderer, &player);
  SDL_RenderFillRect(this->renderer, &npc);
}

void Pong::DrawBall(SDL_Rect& ball)
{
  Ball *PongBall = this->Field->ball;
  ball.x = PongBall->xpos;
  ball.y = PongBall->ypos;
  ball.w = PongBall->width;
  ball.h = PongBall->height;

  SDL_SetRenderDrawColor(this->renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
  SDL_RenderFillRect(this->renderer, &ball);
}

int main(int argc, char *argv[])
{
  bool LeftPaddleUp, LeftPaddleDown, RightPaddleUp, RightPaddleDown;
  SDL_Event event;
  bool quit = false;
  SDL_Rect divideRect, playerRect, npcRect, ballRect;
  Pong Pong;
  Pong.play_has_started = 0;

  LeftPaddleUp = LeftPaddleDown = RightPaddleUp = RightPaddleDown = false;

  float dt = 0.0f;
  float lastTick = 0.0f;
  float currTick = 0.0f;
  if(Pong.Init() < 0)
  {
    cout << "An error occurred with starting Pong. Closing..." << endl;
    return -1;
  }

  lastTick = SDL_GetTicks();
  Pong.DrawPlayingField(divideRect);
  Pong.DrawPaddles(playerRect, npcRect);
  Pong.DrawBall(ballRect);
  SDL_RenderPresent(Pong.renderer);

  currTick = SDL_GetTicks();
  dt = (currTick - lastTick) / 1000;
  while(!quit)
  {
    SDL_PollEvent(&event);
    if(event.type == SDL_QUIT)
    {
      quit = true;
    }

    if(event.type == SDL_KEYDOWN)
    {
      Pong.play_has_started = 1;
      // check which key was pressed
      // and react accordingly
      cout << "Current dt: " << dt << endl;
      switch(event.key.keysym.sym)
      {
        case SDLK_w:
          // move paddle1 up
          LeftPaddleUp = true;
          break;
        case SDLK_s:
          // move paddle1 down
          LeftPaddleDown = true;
          break;
        case SDLK_UP:
          // move paddle2 up
          RightPaddleUp = true;
          break;
        case SDLK_DOWN:
          // move paddle2 down
          RightPaddleDown = true;
          break;
      }
    }

    if(event.type == SDL_MOUSEBUTTONDOWN)
    {
      quit = true;
    }

    if(Pong.play_has_started)
    {
      Pong.Field->MoveBall(dt);
    }

    if(LeftPaddleUp)
    {
        Pong.Field->MovePaddleUp(*(Pong.Field->playerPaddle), dt);
        LeftPaddleUp = false;
    }
    else if(LeftPaddleDown)
    {
        Pong.Field->MovePaddleDown(*(Pong.Field->playerPaddle), dt);
        LeftPaddleDown = false;
    }
    else if(RightPaddleUp)
    {
        Pong.Field->MovePaddleUp(*(Pong.Field->npcPaddle), dt);
        RightPaddleUp = false;
    }
    else if(RightPaddleDown)
    {
        Pong.Field->MovePaddleDown(*(Pong.Field->npcPaddle), dt);
        RightPaddleDown = false;
    }

    Pong.DrawPlayingField(divideRect);
    Pong.DrawPaddles(playerRect, npcRect);
    Pong.DrawBall(ballRect);
    SDL_RenderPresent(Pong.renderer);
    currTick = SDL_GetTicks();
    dt = (currTick - lastTick) / 1000.0f;
    lastTick = currTick;
  }
}
