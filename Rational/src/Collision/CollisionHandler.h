#pragma once
#include <SDL.h>
#include <vector>
#include "../Map/TileLayer.h"
#include "../Map/GameMap.h"


class CollisionHandler
{
public:
	static CollisionHandler* GetInstance() { return s_Instance = (s_Instance != nullptr) ? s_Instance : new CollisionHandler(); }
	bool CheckCollision(SDL_FRect a, SDL_FRect b);
	bool MapCollision(SDL_FRect a);

private:
	CollisionHandler();
	static CollisionHandler* s_Instance;
	TileMap m_CollisionTilemap;
	TileLayer* m_CollisionLayer;
};

