#include "ball.h"

#include "globals.h"

#include <cstdlib>

namespace basg
{
	Ball set(Ball& ball)
	{
		//ball.basketball = LoadTexture("res/basketball.png");
		ball.initPosition = { static_cast<float>(ScreenWidthA / 2), static_cast<float>(ScreenHeightA / 2) };
		ball.position = ball.initPosition;
		ball.speed = { 0.0f, 0.0f };
		ball.radius = 10.0f;
		ball.cap = 10;
		ball.lastTouch = 0;
		
		return ball;
	}

	Ball reset(Ball& ball)
	{
		int directionY = rand() % 2;
		int directionX = rand() % 2;

		ball.position = ball.initPosition;
		ball.speed = {0.0f, 0.0f};
		ball.radius = 10.0f;
		ball.cap = 10;
		ball.lastTouch;

		if (directionX == 0)
		{
			ball.speed.x = -100.0f;
		}
		else if (directionX == 1)
		{
			ball.speed.x = 100.0f;
		}
		if (directionY == 0)
		{
			ball.speed.y = -100.0f;
		}
		else if (directionY == 1)
		{
			ball.speed.y = 100.0f;
		}

		return ball;
	}

	Ball update(Ball& ball, bool changeDirection, Vector2 directionChanger, bool changeSpeed)
	{
		if (changeDirection == true )
		{
			
			ball.speed.x *= directionChanger.x;
			ball.speed.y *= directionChanger.y;
		}
		if (changeSpeed == true && ball.cap > 0)
		{
			ball.speed.x *= 1.2f;
			ball.speed.y *= 1.2f;
			ball.cap--;
		}
		if (ball.speed.x > 0)
		{
			ball.pivot++;
		}
		else if (ball.speed.x < 0)
		{
			ball.pivot--;
		}

		if (ball.position.y - ball.speed.y * GetFrameTime() <= 0)
		{
			ball.position.y = static_cast<float>(ball.radius);
			ball.speed.y *= -1.0f;
		}
		if (ball.position.y + ball.speed.y * GetFrameTime() >= static_cast<float>(ScreenHeightA))
		{
			ball.position.y = static_cast<float>(ScreenHeightA - ball.radius);
			ball.speed.y *= -1.0f;
		}

		ball.position.x += ball.speed.x * GetFrameTime();
		ball.position.y += ball.speed.y * GetFrameTime();



		return ball;
	}

	void draw(Ball ball)
	{
		DrawCircle(static_cast<int>(ball.position.x), static_cast<int>(ball.position.y), ball.radius, ORANGE);
	}

}