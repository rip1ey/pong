#include "PlayingField.h"

#define PI 3.14159265

PlayingField::PlayingField()
{
  int playerX = width / 10;
  int npcX = ((width / 10) * 9) - PADDLE_WIDTH;
  int startY = (height / 2) - (PADDLE_HEIGHT / 2);

  int ballX = (width / 2) - (BALL_WIDTH / 2);
  int ballY = (height / 2) - (BALL_HEIGHT / 2);

  playerPaddle = new Paddle(playerX, startY);
  npcPaddle = new Paddle(npcX, startY);
  ball = new Ball(ballX, ballY);

  player1Score = player2Score = 0;
}

void PlayingField::MovePaddleUp(Paddle& paddle, float dt)
{
  paddle.MoveUp(dt);
  if(paddle.ypos < 0)
  {
    paddle.ypos = 0;
  }
}

void PlayingField::MovePaddleDown(Paddle& paddle, float dt)
{
  paddle.MoveDown(dt);
  if((paddle.ypos + paddle.height) > height)
  {
    paddle.ypos = height - paddle.height;
  }
}

void PlayingField::MoveBall(float dt)
{
  float angle;
  float collision_y, p_sect;
  float paddleF, paddleS, paddleTh, paddleT;
  float intersectPoint = 0.0f;

  p_sect = playerPaddle->height / 3;

  if(ball->xpos > playerPaddle->xpos && ball->xpos < (playerPaddle->xpos + playerPaddle->width))
  {
    if(ball->ypos < (playerPaddle->ypos + playerPaddle->height) && ball->ypos > playerPaddle->ypos)
    {
      collision_y = ball->ypos;
    }
    else if(ball->ypos > playerPaddle->ypos && (ball->ypos + ball->height) < (playerPaddle->ypos + playerPaddle->height))
    {
      collision_y = ball->ypos + (ball->height / 2);
    }
    else if(ball->ypos < (playerPaddle->ypos + playerPaddle->height) && (ball->ypos + ball->height) < (playerPaddle->ypos + playerPaddle->height))
    {
      collision_y = (ball->ypos + ball->height);
    }

    // determine how to reflect the ball
    if(collision_y > playerPaddle->ypos && collision_y < (playerPaddle->ypos + p_sect - 1))
    {
      angle = 150 * (PI / 180);
      ball->velx = ball->speed * sin(angle);
      ball->vely = ball->speed * tan(angle);
    }
    else if(collision_y > (playerPaddle->ypos + p_sect) && collision_y < (playerPaddle->ypos + 2 * p_sect - 1))
    {
      // collision in the middle
      ball->velx = -ball->velx;
      ball->vely = 0;
    }
    else if(collision_y > (playerPaddle->ypos + 2 * p_sect) && collision_y < (playerPaddle->ypos + playerPaddle->height))
    {
      // collision at bottom of paddle
      angle = 60 * (PI / 90);
      ball->velx = ball->speed * sin(angle);
      ball->vely = -ball->speed * tan(angle);
    }
  }
  else if((ball->xpos + ball->width) > npcPaddle->xpos && (ball->xpos + ball->width) < (npcPaddle->xpos + npcPaddle->width))
  {
    if(ball->ypos < (npcPaddle->ypos + npcPaddle->height) && ball->ypos > npcPaddle->ypos)
    {
      collision_y = ball->ypos;
    }
    else if(ball->ypos > npcPaddle->ypos && (ball->ypos + ball->height) < (npcPaddle->ypos + npcPaddle->height))
    {
      collision_y = ball->ypos + (ball->height / 2);
    }
    else if(ball->ypos < (npcPaddle->ypos + npcPaddle->height) && (ball->ypos + ball->height) < (npcPaddle->ypos + npcPaddle->height))
    {
      collision_y = (ball->ypos + ball->height);
    }

    if(collision_y > npcPaddle->ypos && collision_y < (npcPaddle->ypos + p_sect - 1))
    {
      // collision at top of paddle
      angle = 150 * (PI / 180);
      ball->velx = -ball->speed * sin(angle);
      ball->vely = ball->speed * tan(angle);
    }
    else if(collision_y > (npcPaddle->ypos + p_sect) && collision_y < (npcPaddle->ypos + 2 * p_sect - 1))
    {
      // collision in the middle
      ball->velx = -ball->velx;
      ball->vely = 0;
    }
    else if(collision_y > (npcPaddle->ypos + 2 * p_sect) && collision_y < (npcPaddle->ypos + npcPaddle->height))
    {
      // collision at bottom of paddle
      angle = 60 * (PI / 90);
      ball->velx = -ball->speed * sin(angle);
      ball->vely = -ball->speed * tan(angle);
    }
  }
  // just reflect the ball's y velocity when it hits the
  // top or bottom
  else if(ball->ypos < 0 || (ball->ypos + ball->height) > height)
  {
    ball->vely = -ball->vely;
  }
  else if(ball->xpos < 0)
  {
    player2Score++;
    Reset();
  }
  else if(ball->xpos > width)
  {
    player1Score++;
    Reset();
  }

  ball->MoveBall(dt);
}

// set the paddles and ball to its initial state
void PlayingField::Reset()
{
  playerPaddle->xpos = width / 10;
  npcPaddle->xpos = ((width / 10) * 9) - PADDLE_WIDTH;

  int startY = (height / 2) - (PADDLE_HEIGHT / 2);
  playerPaddle->ypos = npcPaddle->ypos = startY;

  ball->xpos = (width / 2) - (BALL_WIDTH / 2);
  ball->ypos = (height / 2) - (BALL_HEIGHT / 2);
  ball->vely = 0.0;

}
