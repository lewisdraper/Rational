#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720
#define WINDOW_NAME "Rational Engine"

class RationalEngine
{
private:
	RationalEngine() {};
	static RationalEngine* s_Instance;
	bool m_IsRunning = false;
	SDL_Window* m_Window;
	SDL_Renderer* m_Renderer;

public:
	static RationalEngine* GetInstance()
	{
		return s_Instance = (s_Instance != nullptr) ? s_Instance : new RationalEngine();
	}

	bool Init();
	bool Clean();
	void Quit();

	void Update();
	void Render();
	void Events();

	inline bool IsRunning() { return m_IsRunning; }
	inline SDL_Renderer* GetRenderer() { return m_Renderer; };

};
