#pragma once

#include "raylib.h"

namespace basg
{
	struct Ball
	{
		Texture2D basketball;
		Vector2 initPosition;
		Vector2 position;
		int width;
		int height;
		int radius;
		Vector2 speed;
	};

	Ball set(Ball& ball, int screenType);
	Ball reset(Ball& ball);
	Ball update(Ball& ball, bool changeDirection, Vector2 directionChanger, bool changeSpeed, int speedChanger);
	void draw(Ball ball);
}
