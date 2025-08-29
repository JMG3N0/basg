#include "ball.h"

#include "globals.h"

namespace basg
{
	Ball set(Ball& ball, int screenType)
	{
		ball.basketball = LoadTexture("Prog1Pong/res/texture/basketball.png");

		switch (screenType)
		{
		case 0:
			ball.initPosition = {(ScreenWidthA/2), (ScreenHeightA/2)};
			break;
		case 1:
			ball.initPosition = { (ScreenWidthB / 2), (ScreenHeightB / 2) };
			break;
		case 2:
			ball.initPosition = { (ScreenWidthC / 2), (ScreenHeightC / 2) };
			break;
		default:
			ball.initPosition = { (ScreenWidthA / 2), (ScreenHeightA / 2) };
			break;
		}
		ball.position = ball.initPosition;
		ball.speed = { 0, 0 };
		ball.radius = 30;
		ball.height = 10;
		ball.width = 10;
	}

	Ball reset(Ball& ball)
	{
		ball.position = ball.initPosition;
		ball.speed = {0, 0};
		ball.radius = 30;
		ball.height = 10;
		ball.width = 10;
	}

	Ball update(Ball& ball, bool changeDirection, Vector2 directionChanger, bool changeSpeed)
	{
		if (changeDirection == true)
		{
			
			ball.speed.x *= directionChanger.x;
			ball.speed.y *= directionChanger.y;
		}
		if (changeSpeed == true)
		{
			ball.speed.x++;
			ball.speed.y++;
		}
	}



}