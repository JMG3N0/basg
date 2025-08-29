#pragma once

namespace basg
{
	enum Menu
	{
		Initial = 0, Play, Options, Credits, Quit
	};

	
	void BootUp();
	void ScreenUpdate();
	void TitleScreen();
	void Gameplay();
	void OptionsScreen();
	void CreditsScreen();
	void QuitGame();
}
