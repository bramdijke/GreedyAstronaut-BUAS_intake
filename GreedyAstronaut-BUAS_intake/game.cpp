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
	
	Sprite player(new Surface("assets/spaceship.tga"), 4);
	Surface spaceBackground("assets/space_background.png");

	void Game::Init()
	{

	}
	void Game::Shutdown()
	{

	}
	void Game::Tick(float deltaTime)
	{
		screen->Clear(0);
		spaceBackground.CopyTo(screen, 0, 0); // Render background image
		player.Draw(screen, px, py); // Draw player

		if (GetAsyncKeyState(VK_LEFT)) px--, player.SetFrame(3);
		if (GetAsyncKeyState(VK_RIGHT)) px++, player.SetFrame(1);
		if (GetAsyncKeyState(VK_UP)) py--, player.SetFrame(0);
		if (GetAsyncKeyState(VK_DOWN)) py++, player.SetFrame(2);
	}
};