#pragma once
#include <SDL.h>

class Game
{
private:
	Game(); //private constructor
public:
	static const int kWidth = 800;
	static const int kHeight = 600;

	static Game& GetInstance();
	int Init(const char* title, int xPos, int yPos);
	bool IsRunning();
	void HandleEvents();
	bool KeyDown(SDL_Scancode key);
	void Update(float deltaTime);
	void Render();
	void Clean();

	SDL_Window* GetWindow() { return g_window; }
	SDL_Renderer* GetRenderer() { return g_Renderer; }

private:
	bool is_running;
	SDL_Window* g_window;
	SDL_Renderer* g_Renderer;
	const Uint8* g_keyState;
};