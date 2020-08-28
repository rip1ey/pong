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
