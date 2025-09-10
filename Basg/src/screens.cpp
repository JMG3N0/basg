#include "screens.h"
#include "player.h"
#include "ball.h"

#include "globals.h"

#include "raylib.h"
#include <cstdlib>
#include <ctime>

namespace basg
{

	Menu Screen;
	Player P1;
	Player P2;
	Ball ball;
	int currentScreenSizeX = ScreenWidthA;
	int currentScreenSizeY = ScreenHeightA;
	int halfScreenX = (currentScreenSizeX / 2);
	int halfScreenY = (currentScreenSizeY / 2);
	int currentScore = 0;
	int directionY = 0;
	int directionX = 0;
	bool P1Active = true;
	bool P2Active = false;
	bool gamePaused = false;
	

	void BootUp()
	{
		InitWindow(currentScreenSizeX, currentScreenSizeY, "Basg");
		srand((unsigned int)time(NULL));
		Screen = Initial;
		SetExitKey(KEY_NULL);
		while (!WindowShouldClose())
		{
			ScreenUpdate();
		}
		CloseWindow();
	}

	void ScreenUpdate()
	{
		BeginDrawing();
		ClearBackground(BLACK);
		switch (Screen)
		{
		case basg::Initial:
			TitleScreen();
			break;
		case basg::Play:
			Gameplay();
			break;
		case basg::Options:
			OptionsScreen();
			break;
		case basg::Credits:
			CreditsScreen();
			break;
		case basg::Quit:
			QuitGame();
			break;
		default:
			break;
		}
		EndDrawing();
	}

	void Gameplay()
	{
		
		draw(ball);
		draw(P1);
		draw(P2);
		
		DrawText(TextFormat("%d", currentScore), (halfScreenX - 10), halfScreenY, 50, GREEN);

		if (P1.score >= 20 || P2.score >= 20)
		{
			ShowCursor();
			DrawRectangle((halfScreenX / 2), (halfScreenY / 2), 400, 300, DARKGRAY);
			if (P1.score >= 20)
			{
				DrawText("Player 1 Won", (halfScreenX - 200), (halfScreenY / 2) + 20, 60, WHITE);
				DrawText(TextFormat("Score: %d", P1.score), (halfScreenX - 60), (halfScreenY)+40, 30, WHITE);

			}
			if (P2.score >= 20)
			{
				DrawText("Player 2 Won", (halfScreenX)-200, (halfScreenY / 2) + 20, 60, WHITE);
				DrawText(TextFormat("Score: %d", P2.score), (halfScreenX - 60), (halfScreenY)+40, 30, WHITE);
			}

			DrawText("Restart", (halfScreenX + 100), halfScreenY + 100, 10, WHITE);
			DrawText("Return to Main Menu", (halfScreenX - 120), halfScreenY + 100, 10, WHITE);

			if (GetMousePosition().y >= (halfScreenY + 90) && GetMousePosition().y <= (halfScreenY + 120))
			{
				if (GetMousePosition().x >= halfScreenX + 70 && GetMousePosition().x <= halfScreenX + 160)
				{
					DrawText("Restart", (halfScreenX + 100), halfScreenY + 100, 10, BLUE);
					if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
					{
						reset(P1);
						reset(P2);
						reset(ball);
						currentScore = 0;
					}
				}
				if (GetMousePosition().x <= halfScreenX && GetMousePosition().x >= halfScreenX - 140)
				{
					DrawText("Return to Main Menu", (halfScreenX - 120), halfScreenY + 100, 10, BLUE);
					if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
					{

						Screen = Initial;
					}
				}
			}
		}

		if (IsKeyPressed(KEY_P) || IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_ESCAPE))
		{
			gamePaused = !gamePaused;
		}

		if (gamePaused == true)
		{
			ShowCursor();
			DrawRectangle((halfScreenX / 2), (halfScreenY / 2), 400, 300, DARKGRAY);
			DrawText("Continue", (halfScreenX + 100), halfScreenY + 70, 15, WHITE);
			DrawText("Return to Main Menu", (halfScreenX - 180), halfScreenY + 70, 15, WHITE);
			if (GetMousePosition().y >= (halfScreenY + 70) && GetMousePosition().y <= (halfScreenY + 100))
			{
				if (GetMousePosition().x >= halfScreenX + 70 && GetMousePosition().x <= halfScreenX + 160)
				{
					DrawText("Continue", (halfScreenX + 100), halfScreenY + 70, 15, BLUE);
					if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
					{
						gamePaused = false;
					}
				}
				if (GetMousePosition().x <= halfScreenX && GetMousePosition().x >= halfScreenX - 180)
				{
					DrawText("Return to Main Menu", (halfScreenX - 180), halfScreenY + 70, 15, BLUE);
					if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
					{

						Screen = Initial;
					}
				}
			}

		}


		if (P1.score < 20 && P2.score < 20 && gamePaused == false)
		{
			HideCursor();
			update(P1, ball);
			update(P2, ball);

			if (collisionPB(P1, ball) == false && collisionPB(P2, ball) == false)
			{
				update(ball, false, { 1.0f, 1.0f }, false);
			}

			if (collisionPB(P1, ball) == true)
			{
				ball.position.x += 50.0f;
				update(ball, true, { -1.0f, 1.0f }, true);
				if (ball.position.y > P1.position.y + P1.height / 2 && ball.speed.y < 0)
				{
					update(ball, true, { 1.0f, -1.0f }, true);
				}
				if (ball.position.y < P1.position.y + P1.height / 2 && ball.speed.y > 0)
				{
					update(ball, true, { 1.0f, -1.0f }, true);
				}
				currentScore++;
			}

			if (collisionPB(P2, ball) == true)
			{
				ball.position.x -= 50.0f;
				update(ball, true, { -1.0f, 1.0f }, true);
				if (ball.position.y > P2.position.y + P2.height/2 && ball.speed.y < 0)
				{
					update(ball, true, { 1.0f, -1.0f }, true);
				}
				if (ball.position.y < P2.position.y + P2.height/2 && ball.speed.y > 0)
				{
					update(ball, true, { 1.0f, -1.0f }, true);
				}
				currentScore++;
			}





			if (ball.position.x - ball.speed.x * GetFrameTime() <= 0 || ball.position.x + ball.speed.x * GetFrameTime() >= ScreenWidthA)
			{
				if (ball.position.x - ball.speed.x * GetFrameTime() <= 0)
				{
					P2.score += currentScore;
				}
				if (ball.position.x + ball.speed.x * GetFrameTime() >= ScreenWidthA)
				{
					P1.score += currentScore;
				}
				reset(P1);
				reset(P2);
				reset(ball);
				currentScore = 0;


			}

		}

	}

	

	void QuitGame()
	{
		
		CloseWindow();
	}

	void OptionsScreen()
	{

		DrawText("Choose how many players will be playing:", (100), halfScreenY - 200, 30, WHITE);
		if (P1Active == true)
		{
			DrawText(">", (230), (halfScreenY - 50), 50, WHITE);
			DrawText("P1", (150), (halfScreenY - 50), 50, WHITE);
			DrawText("<", (100), (halfScreenY - 50), 50, WHITE);
		}
		else 
		{
			DrawText(">", (230), (halfScreenY - 50), 50, WHITE);
			DrawText("AI", (150), (halfScreenY - 50), 50, WHITE);
			DrawText("<", (100), (halfScreenY - 50), 50, WHITE);
			
		}

		if (P2Active == true)
		{
			DrawText(">", (halfScreenX + 235), (halfScreenY - 50), 50, WHITE);
			DrawText("P2", (halfScreenX + 150), (halfScreenY - 50), 50, WHITE);
			DrawText("<", (halfScreenX + 100), (halfScreenY - 50), 50, WHITE);
		}
		else
		{
			DrawText(">", (halfScreenX + 235), (halfScreenY - 50), 50, WHITE);
			DrawText("AI", (halfScreenX + 150), (halfScreenY - 50), 50, WHITE);
			DrawText("<", (halfScreenX + 100), (halfScreenY - 50), 50, WHITE);
		}

		DrawText("Player 1 uses the W,S keys to move. Player 2 uses the Up, Down Arrows", (130), (halfScreenY + 130), 15, WHITE);
		DrawText("Pressing P, Space or ESC will pause the game", (245), (halfScreenY + 155), 15, WHITE);
		DrawText("Use the mouse left click to select a arrow or option", (halfScreenX - 130), (halfScreenY + 180), 10, WHITE);

		DrawText("Play Game", (ScreenWidthA - 100), (ScreenHeightA - 50), 12, WHITE);
		DrawText("Return to Main Menu", 50, (ScreenHeightA - 50), 12, WHITE);

		if (GetMousePosition().x >= (80) && GetMousePosition().x <= (130) && GetMousePosition().y >= (halfScreenY - 60) && GetMousePosition().y <= (halfScreenY - 10))
		{
			DrawText("<", (100), (halfScreenY - 50), 50, BLUE);
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
			{
				P1Active = !P1Active;
				
			}
		}
		if (GetMousePosition().x >= (210) && GetMousePosition().x <= (260) && GetMousePosition().y >= (halfScreenY - 60) && GetMousePosition().y <= (halfScreenY - 10))
		{
			DrawText(">", (230), (halfScreenY - 50), 50, BLUE);
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
			{
				P1Active = !P1Active;
				
			}
		}
		if (GetMousePosition().x >= (halfScreenX + 80) && GetMousePosition().x <= (halfScreenX + 130) && GetMousePosition().y >= (halfScreenY - 60) && GetMousePosition().y <= (halfScreenY - 10))
		{
			DrawText("<", (halfScreenX + 100), (halfScreenY - 50), 50, BLUE);

			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
			{
				P2Active = !P2Active;
				
			}
		}
		if (GetMousePosition().x >= (halfScreenX + 215) && GetMousePosition().x <= (halfScreenX + 265) && GetMousePosition().y >= (halfScreenY - 60) && GetMousePosition().y <= (halfScreenY - 10))
		{
			
			DrawText(">", (halfScreenX + 235), (halfScreenY - 50), 50, BLUE);
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
			{
				P2Active = !P2Active;
				
			}
		}


		if (GetMousePosition().x >= (ScreenWidthA - 120) && GetMousePosition().y >= (ScreenHeightA - 80))
		{
			DrawText("Play Game", (ScreenWidthA - 100), (ScreenHeightA - 50), 12, BLUE);
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
			{
				
				gamePaused = false;
				currentScore = 0;
				set(P1, 0, P1Active);
				set(P2, 1, P2Active);
				set(ball);
				reset(P1);
				reset(P2);
				reset(ball);
				Screen = Play;
			}
		}
		if (GetMousePosition().x <= 200 && GetMousePosition().y >= (ScreenHeightA - 80))
		{
			DrawText("Return to Main Menu", 50, (ScreenHeightA - 50), 12, BLUE);
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
			{
				Screen = Initial;
			}
		}
		

	}
	

	void TitleScreen()
	{


		//Draw Main Menu Text
		DrawText("Basg", (halfScreenX - 50), halfScreenY - 40, 30, WHITE);
		DrawText("Play", (halfScreenX - 30), (halfScreenY + 20), 15, WHITE);
		DrawText("Credits", (halfScreenX - 30), (halfScreenY + 50), 15, WHITE);
		DrawText("Exit", (halfScreenX - 30), (halfScreenY + 80), 15, WHITE);
		DrawText("Use the mouse left click to select a option", (halfScreenX - 120), (halfScreenY + 150), 10, WHITE);


		if (GetMousePosition().x >= (halfScreenX - 40) && GetMousePosition().x <= (halfScreenX + 20))
		{
			if (GetMousePosition().y >= (halfScreenY + 10) && GetMousePosition().y <= (halfScreenY + 35))
			{
				DrawText("Play", (halfScreenX - 30), (halfScreenY + 20), 15, BLUE);
				if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
				{
					Screen = Options;
				}
			}
			if (GetMousePosition().y >= (halfScreenY + 40) && GetMousePosition().y <= (halfScreenY + 65))
			{
				DrawText("Credits", (halfScreenX - 30), (halfScreenY + 50), 15, BLUE);
				if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
				{
					Screen = Credits;
				}
			}
			if (GetMousePosition().y >= (halfScreenY + 70) && GetMousePosition().y <= (halfScreenY + 95))
			{
				DrawText("Exit", (halfScreenX - 30), (halfScreenY + 80), 15, BLUE);
				if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
				{
					Screen = Quit;
				}
			}

		}
	}

	void CreditsScreen()
	{


		DrawText("Game made by Joan Manuel Rivas Cepeda", (halfScreenX - 200), halfScreenY, 20, WHITE);
		DrawText("Play Game", (halfScreenX + 100), halfScreenY + 100, 10, WHITE);
		DrawText("Return to Main Menu", (halfScreenX - 120), halfScreenY + 100, 10, WHITE);

		if (GetMousePosition().y >= (halfScreenY + 90) && GetMousePosition().y <= (halfScreenY + 120))
		{
			if (GetMousePosition().x >= halfScreenX + 70 && GetMousePosition().x <= halfScreenX + 160)
			{
				DrawText("Play Game", (halfScreenX + 100), halfScreenY + 100, 10, BLUE);
				if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
				{
					Screen = Options;
				}
			}
			if (GetMousePosition().x <= halfScreenX && GetMousePosition().x >= halfScreenX - 140)
			{
				DrawText("Return to Main Menu", (halfScreenX - 120), halfScreenY + 100, 10, BLUE);
				if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
				{
					Screen = Initial;
				}
			}
		}

	}
}