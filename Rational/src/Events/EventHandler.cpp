#include "EventHandler.h"
#include "../Core/RationalEngine.h"

EventHandler* EventHandler::s_Instance = nullptr;

EventHandler::EventHandler()
{
	m_KeyStates = SDL_GetKeyboardState(nullptr);
}

void EventHandler::Listen()
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			RationalEngine::GetInstance()->Quit();
			break;

		case SDL_KEYDOWN:
			KeyDown();
			break;

		case SDL_KEYUP:
			KeyUp();
			break;
		}
	}
}

bool EventHandler::GetKeyDown(SDL_Scancode key)
{
	return m_KeyStates[key] == 1;
}

void EventHandler::KeyUp()
{
	m_KeyStates = SDL_GetKeyboardState(nullptr);
}

void EventHandler::KeyDown()
{
	m_KeyStates = SDL_GetKeyboardState(nullptr);
}
