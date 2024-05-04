#include "game.h"
#include "surface.h"
#include <cstdio> //printf
#include <windows.h>
#include "template.h"
#define WIN32_LEAN_AND_MEAN


namespace Tmpl8
{
	Sprite player(new Surface("assets/spaceship.png"), 1);
	Surface spaceBackground("assets/space_background.png");
	int screenX = ScreenWidth, screenY = ScreenHeight;
	int px = screenX / 2 - 18, py = screenY / 2 - 18; 

	void Game::Init()
	{

	}
	void Game::Shutdown()
	{

	}
	void Game::Tick(float deltaTime)
	{
		screen->Clear(0);
		// Draw background image
		spaceBackground.CopyTo(screen, 0, 0);
		player.Draw(screen, px, py);

		if (GetAsyncKeyState(VK_LEFT)) px--;
		if (GetAsyncKeyState(VK_RIGHT)) px++;
		if (GetAsyncKeyState(VK_UP)) py--;
		if (GetAsyncKeyState(VK_DOWN)) py++;
	}
};