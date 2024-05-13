#include "game.h"
#include "surface.h"
#include <cstdio> //printf
#include <cstdlib>
#include <windows.h>
#include "template.h"
#include <SDL_mouse.h>
#include "template.h"
#define WIN32_LEAN_AND_MEAN


namespace Tmpl8
{
	int screenX = ScreenWidth, screenY = ScreenHeight; // Get screen sizes
	int px = screenX / 2 - 18, py = screenY / 2 - 18; // Place player in center of screen
	int gemX[10], gemY[10]; // 10 values for coordinates of gems
	
	Sprite player(new Surface("assets/spaceship.tga"), 4); // Player sprite
	Surface menuBackground("assets/menu_background.png"); // Space background sprite
	Surface spaceBackground("assets/space_background.png"); // Space background sprite

	Sprite titleLogo(new Surface("assets/gameTitle.png"), 1); // Title logo sprite
	Sprite playSprite(new Surface("assets/playButton.png"), 1); // Play button sprite
	Sprite quitSprite(new Surface("assets/quitButton.png"), 1); // Quit button sprite

	Sprite gemSprite(new Surface("assets/gem.png"), 1); // Gem sprite

	 bool timerStarted = false;

	void Game::Init() //Runs when program initializes
	{
		gem.Init();
	}
	void Game::Shutdown() // Runs when programs shuts down
	{

	}
	void Game::Tick(float deltaTime) // Runs every tick
	{
		switch (state)
		{
		case GameState::menuState: // This is the state of the menu screen
			MenuScreen(deltaTime);
			break;
		case GameState::gameState: // This is the state of the game screen
			GameScreen(deltaTime);
			if (!timerStarted) { // Checks if timer has started. If not, it starts the timer.
				timer.Start(); 
				timerStarted = true;  // Sets timerStarted to true so it won't keep resetting timer to 60 seconds
			}
			break;
		case GameState::scoreState: // This is the state of the score screen
			ScoreScreen(deltaTime);
			break;
		}

	}

	void Game::MenuScreen(float deltaTime) // Runs when in menu screen
	{
		menuBackground.CopyTo(screen, 0, 0); // Render background image
		titleLogo.Draw(screen, 90, 100); // Render title image
		playSprite.Draw(screen, 100, 250); // Render play button image
		quitSprite.Draw(screen, 100, 300); // Render quit button image
	}

	void Game::GameScreen(float deltaTime) // Runs when in game screen
	{
		screen->Clear(0);

		timer.Update();

		spaceBackground.CopyTo(screen, 0, 0);

		for (int i = 0; i < 5; i++)
		{
			if (!gem.CheckCollision(px, py, player.GetWidth(), player.GetHeight())) // Check if the player hasn't collided with the gem
			{
				gem.Draw(screen, gem.x[i], gem.y[i]); // If no collision, draw the gem at its position
			}
			else
			{
				score.IncrementScore(); // Increment score when collision occurs
			}
		}

		player.Draw(screen, px, py); // Draw player

		if (GetAsyncKeyState(VK_LEFT) && px > 0) px -= 4, player.SetFrame(3);
		if (GetAsyncKeyState(VK_RIGHT) && px < screenX - player.GetWidth()) px += 4, player.SetFrame(1);
		if (GetAsyncKeyState(VK_UP) && py > 0) py -= 4, player.SetFrame(0);
		if (GetAsyncKeyState(VK_DOWN) && py < screenY - player.GetHeight()) py += 4, player.SetFrame(2);

		char scoreText[15]; // 14 digits at most
		sprintf(scoreText, "Score: %d", score.GetScore());
		screen->Print(scoreText, 10, 10, Pixel(255 << 16) + (255 << 8) + (255));

		char timeText[15]; // 14 digits at most
		sprintf(timeText, "Time: %ds", timer.GetDuration());
		screen->Print(timeText, 620, 10, Pixel(255 << 16) + (255 << 8) + (255));
	}

	void Game::ScoreScreen(float deltaTime) // Runs when in score screen
	{
		spaceBackground.CopyTo(screen, 0, 0);
	}

	void Game::MouseDown(int button) { // Runs when mouse is pressed down
		if (button == SDL_BUTTON_LEFT && state == GameState::menuState) {

			// If-statement to change to gameState. If mouse coordinates are within coordinates of plau button, the state changes to gameState
			if (mousex > 100 && mousex < 100 + playSprite.GetWidth() &&
				mousey > 250 && mousey < 250 + playSprite.GetHeight()) {
				state = GameState::gameState;
			}

			// If-statement to close program. If mouse coordinates are within coordinates of quit button, the program closes
			if (mousex > 100 && mousex < 100 + quitSprite.GetWidth() &&
				mousey > 300 && mousey < 300 + quitSprite.GetHeight()) {
				exit(0);
			}
		}
	}
	
};