#include "Pong.h"

//#define DEBUG_PONG
#define FONT_HEIGHT 100
#define FONT_WIDTH  50
#define MID_OFFSET 20

int Pong::Init()
{
  if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) != 0)
  {
    SDL_Log("Failed to initialize SDL: %s\n", SDL_GetError());
    return -1;
  }

  if(TTF_Init() < 0)
  {
    SDL_Log("Failed to initialize SDL_TTF: %s\n", TTF_GetError());
    return -1;
  }

  font = TTF_OpenFont("./font/retro_font.ttf", 24);
  if(font == NULL)
  {
    SDL_Log("Failed to open font: %s\n", TTF_GetError());
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

int Pong::HaveWinner()
{
  return (this->Field->player1Score == 10 || this->Field->player2Score == 10);
}

void Pong::ResetGame()
{
  this->Field->Reset();
  this->Field->player1Score = 0;
  this->Field->player2Score = 0;
}

/*
 * This needs to first convert the
 * integer value to a string to be
 * used with an SDL_Texture.
 */
void Pong::RenderScores()
{
  char P1ScoreStr[2], P2ScoreStr[2];
  SDL_Texture *P1Text, *P2Text;

  SDL_Color color = { 255, 255, 255 };

  snprintf(P1ScoreStr, 2, "%d", this->Field->player1Score);
  snprintf(P2ScoreStr, 2, "%d", this->Field->player2Score);
  
  P1ScoreSurf = TTF_RenderText_Solid(this->font, P1ScoreStr, color);
  P2ScoreSurf = TTF_RenderText_Solid(this->font, P2ScoreStr, color);
  if(!P1ScoreSurf || !P2ScoreSurf)
  {
    SDL_Log("Failed to create surface:%s\n", SDL_GetError());
    return;
  }

  P1Text = SDL_CreateTextureFromSurface(this->renderer, P1ScoreSurf);
  P2Text = SDL_CreateTextureFromSurface(this->renderer, P2ScoreSurf);

  float ScoreY = 20;
  float MidPoint = this->Field->width / 2.0;
  float P1X = MidPoint - (MID_OFFSET + FONT_WIDTH + (this->Field->divider / 2.0));
  float P2X = MidPoint + MID_OFFSET + (this->Field->divider / 2.0);
  SDL_Rect P1Rect = { P1X, ScoreY, FONT_WIDTH, FONT_HEIGHT };
  SDL_Rect P2Rect = { P2X, ScoreY, FONT_WIDTH, FONT_HEIGHT };
  SDL_RenderCopy(this->renderer, P1Text, NULL, &P1Rect);
  SDL_RenderCopy(this->renderer, P2Text, NULL, &P2Rect);

  SDL_DestroyTexture(P1Text);
  SDL_DestroyTexture(P2Text);
}

int main(int argc, char *argv[])
{
  SDL_Event event;
  bool quit = false;
  SDL_Rect divideRect, playerRect, npcRect, ballRect;
  Pong Pong;
  Pong.play_has_started = 0;

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
  Pong.RenderScores();
  SDL_RenderPresent(Pong.renderer);

  currTick = SDL_GetTicks();
  dt = (currTick - lastTick) / 1000;
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
        Pong.play_has_started = 1;
        if(event.key.keysym.sym == SDLK_ESCAPE)
        {
          quit = true;
        }
      }
    }
    
    const Uint8 *KeyStates = SDL_GetKeyboardState(NULL);
    if(KeyStates[SDL_SCANCODE_W])
    {
        Pong.Field->MovePaddleUp(*(Pong.Field->playerPaddle), dt);
    }
    else if(KeyStates[SDL_SCANCODE_S])
    {
        Pong.Field->MovePaddleDown(*(Pong.Field->playerPaddle), dt);
    }
    else if(KeyStates[SDL_SCANCODE_UP])
    {
        Pong.Field->MovePaddleUp(*(Pong.Field->npcPaddle), dt);
    }
    else if(KeyStates[SDL_SCANCODE_DOWN])
    {
        Pong.Field->MovePaddleDown(*(Pong.Field->npcPaddle), dt);
    }

    if(Pong.play_has_started)
    {
      Pong.Field->MoveBall(dt);
    }

    Pong.DrawPlayingField(divideRect);
    Pong.DrawPaddles(playerRect, npcRect);
    Pong.DrawBall(ballRect);
    Pong.RenderScores();
    SDL_RenderPresent(Pong.renderer);
    currTick = SDL_GetTicks();
    dt = (currTick - lastTick) / 1000.0f;
    lastTick = currTick;

    if(Pong.HaveWinner())
    {
      Pong.ResetGame();
    }
  }
}
