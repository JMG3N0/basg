#pragma once

#include "raylib.h"

namespace basg
{
	struct Ball
	{
		//Texture2D basketball;
		Vector2 initPosition;
		Vector2 position;
		Vector2 speed;
		int width;
		int height;
		float radius;
		int cap;
		int lastTouch;
		float pivot;
	};

	Ball set(Ball& ball);
	Ball reset(Ball& ball);
	Ball update(Ball& ball, bool changeDirection, Vector2 directionChanger, bool changeSpeed);
	void draw(Ball ball);
	
}
