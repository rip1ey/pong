#include "PlayingField.h"

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

void PlayingField::MovePaddleUp(Paddle& paddle, unsigned int dt)
{
  paddle.MoveUp(dt);
  if(paddle.ypos < 0)
  {
    paddle.ypos = 0;
  }
}

void PlayingField::MovePaddleDown(Paddle& paddle, unsigned int dt)
{
  paddle.MoveDown(dt);
  if((paddle.ypos + paddle.height) > height)
  {
    paddle.ypos = height - paddle.height;
  }
}

void PlayingField::MoveBall(unsigned int dt)
{
  int range, sect, intersection;

  ball->MoveBall(dt);
  if((ball->xpos < playerPaddle->xpos + playerPaddle->width) && (ball->xpos > playerPaddle->xpos))
  {
    // check which region of the paddle the collision occurred
    // *if* the collision actually occurred
    // The y value of the ball needs to be within the range of
    // the paddle
    if((ball->ypos > playerPaddle->ypos && ball->ypos < playerPaddle->ypos + playerPaddle->height)
        || (ball->ypos + ball->height > playerPaddle->ypos && ball->ypos + ball->height < playerPaddle->ypos + playerPaddle->height)
        || (ball->ypos < playerPaddle->ypos + playerPaddle->height && ball->ypos + ball->height > playerPaddle->ypos + playerPaddle->height))
    {
      range = playerPaddle->height / 3; // split paddle into three sections
      intersection = (ball->ypos + ball->height / 2); // find the midpoint of the ball and determine which section was hit
      cout << "Ranges..." << endl;
      cout << "Paddle range: " << range << endl;
      cout << "Paddle position, paddle height: " << playerPaddle->ypos << ", " << playerPaddle->ypos + playerPaddle->height << endl;;
      cout << "Midpoint of ball: " << intersection << endl;
      if(intersection > playerPaddle->ypos && intersection < playerPaddle->ypos + range - 1)
      {
        // ball hits top of paddle
        cout << "Ball hit top" << endl;
        ball->velx = cos(75);
        ball->vely = sin(75);
      }
      else if(intersection > playerPaddle->ypos + range && intersection < playerPaddle->ypos + (2 * range) - 1)
      {
        // ball hits middle
        cout << "Ball hit middle" << endl;
        ball->velx = -ball->velx;
      }
      else if(intersection > playerPaddle->ypos + (2 * range) && intersection < playerPaddle->ypos + playerPaddle->height)
      {
        // ball hits bottom of paddle
        cout << "Ball hit bottom" << endl;
        ball->velx = cos(45);
        ball->vely = sin(45);
      }
    }
  }
  else if((ball->xpos + ball->width > npcPaddle->xpos) && (ball->xpos < npcPaddle->xpos + npcPaddle->width))
  {
    if(ball->ypos > npcPaddle->ypos && ball->ypos < npcPaddle->ypos + npcPaddle->height)
    {
      ball->velx = -ball->velx;
    }
  }

  // handle top and bottom collisions
  if(ball->ypos < 0)
  {
    ball->vely = -ball->vely;
  }
}

void PlayingField::Reset()
{

}
