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

		if (!timerStarted)
		{
			timer.Start();
			timerStarted = true;
		}

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

		// Print time left on screen
		char timeText[15]; // 14 digits at most
		sprintf(timeText, "Time: %ds", timer.GetDuration());
		screen->Print(timeText, 620, 10, Pixel(255 << 16) + (255 << 8) + (255));

		// Print score on screen
		char scoreText[15]; // 14 digits at most
		sprintf(scoreText, "Score: %d", score.GetScore());
		screen->Print(scoreText, 10, 10, Pixel(255 << 16) + (255 << 8) + (255));

		// If-statement to switch the state to scoreState when the timer has finished
		if (timer.IsFinished()) 
		{
			state = GameState::scoreState;
		}

	}

	void Game::ScoreScreen(float deltaTime) // Runs when in score screen
	{
		screen->Clear(0);

		// If-statement to check if the current score is higher than the current score
		if (score.GetScore() > highscore) {
			highscore = score.GetScore(); // Update highscore if necessary
		}

		// Print score on screen
		char scoreText[15]; // 14 digits at most
		sprintf(scoreText, "Score: %d", score.GetScore());
		screen->Print(scoreText, 300, 200, Pixel(255 << 16) + (255 << 8) + (255));

		// Print highscore on screen
		char highscoreText[15]; // 14 digits at most
		sprintf(highscoreText, "Highscore: %d", highscore);
		screen->Print(highscoreText, 300, 240, Pixel(255 << 16) + (255 << 8) + (255));
	}

	void Game::MouseDown(int button) { // Runs when mouse is pressed down
		if (state == GameState::menuState) {
			// Check for button clicks only in the menu state
			if (button == SDL_BUTTON_LEFT) {
				// Check if the mouse coordinates are within the play button area
				if (mousex > 100 && mousex < 100 + playSprite.GetWidth() &&
					mousey > 250 && mousey < 250 + playSprite.GetHeight()) {
					state = GameState::gameState; // Change to game state
				}
				// Check if the mouse coordinates are within the quit button area
				else if (mousex > 100 && mousex < 100 + quitSprite.GetWidth() &&
					mousey > 300 && mousey < 300 + quitSprite.GetHeight()) {
					exit(0); // Quit the program
				}
			}
		}
		else if (state == GameState::scoreState) {
			// Check for mouse clicks during the score screen
			if (button == SDL_BUTTON_LEFT) {
				// Change state to menuState if clicked anywhere on the screen
				state = GameState::menuState;
			}
		}
	}
	
};