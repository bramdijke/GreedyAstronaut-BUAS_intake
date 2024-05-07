#pragma once

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
	void SetTarget( Surface* surface ) { screen = surface; }
	void Init();
	void Shutdown();
	void Tick( float deltaTime );
	void MouseUp( int button ) { /* implement if you want to detect mouse button presses */ }
	void MouseDown( int button ) { /* implement if you want to detect mouse button presses */ }
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
};



}; // namespace Tmpl8