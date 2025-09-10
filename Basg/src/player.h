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
		float speed;
		bool isAlive;
	};

	Player set(Player& player, int team, bool isAlive);
	Player reset(Player& player);
	Player update(Player& player, Ball b);
	void draw(Player player);
	bool collisionPB(Player P, Ball B);

}
