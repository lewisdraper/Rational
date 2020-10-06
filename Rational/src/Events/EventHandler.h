#pragma once
#include <SDL.h>

class EventHandler {
public:
	static EventHandler* GetInstance()
	{
		return s_Instance = (s_Instance != nullptr) ? s_Instance : new EventHandler();
	}

	void Listen();
	bool GetKeyDown(SDL_Scancode key);


private:
	EventHandler();
	void KeyUp();
	void KeyDown();

	const Uint8* m_KeyStates;

	static EventHandler* s_Instance;

};