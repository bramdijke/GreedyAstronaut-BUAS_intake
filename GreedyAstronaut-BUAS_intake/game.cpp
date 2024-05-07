#include "game.h"
#include "surface.h"
#include <cstdio> //printf
#include <windows.h>
#include "template.h"
#define WIN32_LEAN_AND_MEAN


namespace Tmpl8
{
	int screenX = ScreenWidth, screenY = ScreenHeight; // Get screen sizes
	int px = screenX / 2 - 18, py = screenY / 2 - 18; // Place player in center of screen
	
	Sprite player(new Surface("assets/spaceship.tga"), 4); // Player sprite
	Surface spaceBackground("assets/space_background.png"); // Space background sprite

	Sprite titleLogo(new Surface("assets/gameTitle.png"), 1); // Title logo sprite
	Sprite playSprite(new Surface("assets/playButton.png"), 1); // Play button sprite
	Sprite quitSprite(new Surface("assets/quitButton.png"), 1); // Quit button sprite

	void Game::Init() //Runs when program initializes
	{
	}
	void Game::Shutdown() // Runs when programs shuts down
	{

	}
	void Game::Tick(float deltaTime) // Runs every tick
	{
		switch (state)
		{
		case GameState::menuState:
			MenuScreen(deltaTime);
			break;
		case GameState::gameState:
			GameScreen(deltaTime);
			break;
		case GameState::scoreState:
			ScoreScreen(deltaTime);
			break;
		}

	}

	void Game::MenuScreen(float deltaTime) // Runs when in menu screen
	{
		screen->Clear(0);
		spaceBackground.CopyTo(screen, 0, 0); // Render background image
		player.Draw(screen, px, py); // Draw player

		screen->Line(mousex, 0, mousex, 511, 0xff0000); // for testing
		screen->Line(0, mousey, 799, mousey, 0xff0000); // for testing

		if (GetAsyncKeyState(VK_LEFT)) px--, player.SetFrame(3);
		if (GetAsyncKeyState(VK_RIGHT)) px++, player.SetFrame(1);
		if (GetAsyncKeyState(VK_UP)) py--, player.SetFrame(0);
		if (GetAsyncKeyState(VK_DOWN)) py++, player.SetFrame(2);

	}

	void Game::GameScreen(float deltaTime) // Runs when in game screen
	{

	}

	void Game::ScoreScreen(float deltaTime) // Runs when in score screen
	{

	}
};