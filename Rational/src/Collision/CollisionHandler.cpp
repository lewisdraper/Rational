#include "CollisionHandler.h"
#include "../Core/RationalEngine.h"



CollisionHandler* CollisionHandler::s_Instance = nullptr;

CollisionHandler::CollisionHandler() {
	m_CollisionLayer = (TileLayer*)RationalEngine::GetInstance()->GetMap()->GetMapLayers().back();
	m_CollisionTilemap = m_CollisionLayer->GetTileMap();
}

//Checks if the rectangles "a" & "b" overlap eachother
bool CollisionHandler::CheckCollision(SDL_FRect a, SDL_FRect b)
{
	bool x_overlaps = (a.x < b.x + b.w) && (a.x + a.w > b.x);
	bool y_overlaps = (a.y < b.y + b.h) && (a.y + a.h > b.y);

	return x_overlaps && y_overlaps;
}

//Checks if rectangle "a" is currently colliding with the collision map
bool CollisionHandler::MapCollision(SDL_FRect a)
{
	int tileSize = 32;
	int rowCount = 24;
	int colCount = 48;

	int leftTile = a.x / tileSize;
	int rightTile = (a.x + a.w) / tileSize;
	int topTile = a.y / tileSize;
	int bottomTile = (a.y + a.h) / tileSize;

	if (leftTile < 0)
		leftTile = 0;

	if (rightTile > colCount)
		rightTile = colCount;

	if (topTile < 0)
		topTile = 0;

	if (bottomTile > rowCount)
		bottomTile = rowCount;

	for (int i = leftTile; i <= rightTile; i++)
	{
		for (int j = topTile; j <= bottomTile; j++)
		{
			if (int t = m_CollisionTilemap[j][i] > 0)
			{
				return true;
			}
		}

	}

	return false;

}
