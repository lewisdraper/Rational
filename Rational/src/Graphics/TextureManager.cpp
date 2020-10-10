#include "TextureManager.h"
#include "../Core/RationalEngine.h"
#include "../Camera/Camera.h"

TextureManager* TextureManager::s_Instance = nullptr;

bool TextureManager::Load(std::string id, std::string filename)
{
	SDL_Surface* surface = IMG_Load(filename.c_str());
	if (surface == nullptr)
	{
		SDL_Log("Failed to load texture %s: %s", filename.c_str(), SDL_GetError());
		return false;
	}

	SDL_Texture* texture = SDL_CreateTextureFromSurface(RationalEngine::GetInstance()->GetRenderer(), surface);
	if (texture == nullptr)
	{
		SDL_Log("Failed to create texture from surface: %s", SDL_GetError());
		return false;
	}

	m_TextureMap[id] = texture;
	return true;
}

void TextureManager::Drop(std::string id)
{
	SDL_DestroyTexture(m_TextureMap[id]);
	m_TextureMap.erase(id);
}

void TextureManager::Clean()
{
	std::map<std::string, SDL_Texture*>::iterator it;
	for (it = m_TextureMap.begin(); it != m_TextureMap.end(); it++)
		SDL_DestroyTexture(it->second);

	m_TextureMap.clear();

	SDL_Log("Texture Map Cleaned");
}

#pragma warning( push )
#pragma warning( disable : 26812)
void TextureManager::Draw(std::string id, float x, float y, int srcW, int srcH, float dstW, float dstH, SDL_RendererFlip flip)
{
	SDL_Rect srcRect = { 0, 0, srcW, srcH };

	Vector2D cam = Camera::GetInstance()->GetPosition();
	SDL_FRect dstRect = { x - cam.X * 0.3, y - cam.Y * 0.3, dstW, dstH };
	SDL_RenderCopyExF(RationalEngine::GetInstance()->GetRenderer(), m_TextureMap[id], &srcRect, &dstRect, 0, nullptr, flip);
}

void TextureManager::DrawFrame(std::string id, float x, float y, int srcW, int srcH, float dstW, float dstH, int row, int frame, SDL_RendererFlip flip)
{
	SDL_Rect srcRect = { srcW * frame, srcH * (row-1), srcW, srcH };

	Vector2D cam = Camera::GetInstance()->GetPosition();
	SDL_FRect dstRect = { x - cam.X, y - cam.Y, dstW , dstH };
	SDL_RenderCopyExF(RationalEngine::GetInstance()->GetRenderer(), m_TextureMap[id], &srcRect, &dstRect, 0, nullptr, flip);
}

void TextureManager::DrawTile(std::string tilesetId, int tileSize, float x, float y, float scale, int row, int frame, SDL_RendererFlip flip)
{
	SDL_Rect srcRect = { tileSize * frame, tileSize * row, tileSize, tileSize };

	Vector2D cam = Camera::GetInstance()->GetPosition();
	SDL_FRect dstRect = { x * scale - cam.X , y * scale - cam.Y, tileSize* scale, tileSize* scale };
	SDL_RenderCopyExF(RationalEngine::GetInstance()->GetRenderer(), m_TextureMap[tilesetId], &srcRect, &dstRect, 0, 0, flip);
}
#pragma warning( pop ) 