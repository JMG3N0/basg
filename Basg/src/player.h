#pragma once

#include "raylib.h"

#include "ball.h"

namespace basg
{
	struct Player
	{
		Vector2 initPosition;
		Vector2 position;
		int height;
		int width;
		int score;
		int team;
		int number;
		bool isAlive;
	};

	Player set(Player& player, int number, int team, bool isAlive);
	Player reset(Player& player);
	Player update(Player& player);
	bool collisionPB(Player P, Ball B);
	void draw(Player player);
}
