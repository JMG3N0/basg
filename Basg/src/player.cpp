#pragma once

#include "player.h"
#include "raylib.h"
#include "globals.h"

namespace basg
{
	Player set(Player& player, int team, bool isAlive)
	{
		player.team = team;
		player.isAlive = isAlive;

		if (player.team == 0)
		{
			player.initPosition.x = 10;
			
		}
		else if (player.team == 1)
		{
			player.initPosition.x = static_cast<float>(ScreenWidthA-10);
		}
		player.initPosition.y = static_cast<float>(ScreenHeightA / 2);

		player.position = player.initPosition;

		player.score = 0;

		player.height = 50;
		player.width = 5;
		player.speed = 150.0f;
		return player;
	}

	Player reset(Player& player)
	{
		player.position = player.initPosition;
		player.score = 0;
		return player;
	}

	Player update(Player& player, Ball b)
	{
		if (player.isAlive == true)
		{
			if (player.team == 0)
			{
				if (IsKeyDown(KEY_W) && player.position.y - player.speed * GetFrameTime() > 0.0f)
				{
					player.position.y -= player.speed * GetFrameTime();
				}
				if (IsKeyDown(KEY_S) && player.position.y + player.height + player.speed * GetFrameTime() < static_cast<float>(ScreenHeightA))
				{
					player.position.y += player.speed * GetFrameTime();
				}
			}
			else if (player.team == 1)
			{
				if (IsKeyDown(KEY_UP) && player.position.y - player.speed * GetFrameTime() > 0.0f)
				{
					player.position.y -= player.speed * GetFrameTime();
				}
				if (IsKeyDown(KEY_DOWN) && player.position.y + player.height + player.speed * GetFrameTime() < static_cast<float>(ScreenHeightA))
				{
					player.position.y += player.speed * GetFrameTime();
				}
			}
		}
		else
		{
			if (b.position.y + b.height > player.position.y + player.height  && player.position.y + player.speed * GetFrameTime() < ScreenHeightA)
			{
				player.position.y += player.speed * GetFrameTime();
			}
			if (b.position.y - b.height < player.position.y - player.height  && player.position.y - player.speed * GetFrameTime() > 0)
			{
				player.position.y -= player.speed * GetFrameTime();
			}
		}
		return player;
	}

	void draw(Player player)
	{
		DrawRectangle(static_cast<int>(player.position.x), static_cast<int>(player.position.y), player.width, player.height, WHITE);
		DrawText(TextFormat("%d", player.score), static_cast<int>(player.position.x), static_cast<int>(player.position.y + player.height/4), 20, GRAY);
	}

	bool collisionPB(Player P, Ball B)
	{
		if (P.team == 0)
		{
			if (B.position.x - B.speed.x * GetFrameTime() <= P.position.x - static_cast<float>(P.width) && B.position.y + B.speed.y * GetFrameTime() <= P.position.y + static_cast<float>(P.height+10) && B.position.y - B.speed.y * GetFrameTime() >= P.position.y-10.0f)
			{
				return true;
			}
			else false;
		}
		else if (P.team == 1)
		{
			if (B.position.x + B.speed.x * GetFrameTime() >= P.position.x + static_cast<float>(P.width) && B.position.y  + B.speed.y * GetFrameTime() <= P.position.y + static_cast<float>(P.height+10) && B.position.y - B.speed.y * GetFrameTime() >= P.position.y-10.0f)
			{
				return true;
			}
			else false;
		}
		return false;
	}
}