#include "PlayingField.h"

PlayingField::PlayingField()
{
	int playerX = width / 10;
	int startY = height * (3 / 4);
	playerPaddle = new Paddle(playerX, startY);
}
