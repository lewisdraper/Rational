#include "RationalEngine.h"
#include "../Graphics/TextureManager.h"
#include "../Character/Bertie.h"
#include "../Events/EventHandler.h"

RationalEngine* RationalEngine::s_Instance = nullptr;
Bertie* bert = nullptr;

bool RationalEngine::Init()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0 && IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) != 0)
	{
		SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
		return false;
	}

	SDL_Log("Successfully Initialized SDL!");

	m_Window = SDL_CreateWindow(WINDOW_NAME, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
	if (m_Window == NULL)
	{
		SDL_Log("Failed to create window: %s", SDL_GetError());
	}

	m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (m_Renderer == NULL)
	{
		SDL_Log("Failed to create renderer: %s", SDL_GetError());
	}

	TextureManager::GetInstance()->Load("bertWalking", "assets/bertwalk.png");
	TextureManager::GetInstance()->Load("bertIdle", "assets/bertidle.png");
	bert = new Bertie(new Properties("bertIdle", 0, 0, 64, 64));
	
	m_IsRunning = true;
	return m_IsRunning;
}

void RationalEngine::Update()
{
	bert->Update(0);
}

void RationalEngine::Render()
{
	SDL_SetRenderDrawColor(m_Renderer, 102, 178, 255, 255);
	SDL_RenderClear(m_Renderer);

	bert->Draw();

	SDL_RenderPresent(m_Renderer);
}

void RationalEngine::Events()
{
	EventHandler::GetInstance()->Listen();
}

bool RationalEngine::Clean()
{
	TextureManager::GetInstance()->Clean();
	SDL_DestroyWindow(m_Window);
	SDL_DestroyRenderer(m_Renderer);
	IMG_Quit();
	SDL_Quit();

	return true;
}

void RationalEngine::Quit()
{
	m_IsRunning = false;
}

