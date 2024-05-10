#pragma once
#include "surface.h"
#include "score.h"

namespace Tmpl8 {

class Surface;
enum class GameState {
	menuState,
	gameState,
	scoreState,
};
class Game

{
public:
	Game() : score() {}
	void SetTarget( Surface* surface ) { screen = surface; }
	void Init();
	void Shutdown();
	void Tick( float deltaTime );
	void MouseUp( int button ) { /* implement if you want to detect mouse button presses */ }
	void MouseDown(int button);
	void MouseMove(int x, int y) { mousex = x, mousey = y; } /*Mouse movement*/
	void KeyUp( int key ) { /* implement if you want to handle keys */ }
	void KeyDown( int key ) { /* implement if you want to handle keys */ }

	void MenuScreen(float deltaTime); // function for menu screen
	void GameScreen(float deltaTime); // function for game screen
	void ScoreScreen(float deltaTime); // function for score screen

private:
	Surface* screen;
	int mousex, mousey;
	GameState state = GameState::menuState;

	float time = 0.0f;
	Score score;
};



}; // namespace Tmpl8