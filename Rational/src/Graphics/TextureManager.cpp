#include "TextureManager.h"
#include "../Core/RationalEngine.h"

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

void TextureManager::Draw(std::string id, int x, int y, int w, int h, SDL_RendererFlip flip)
{
	SDL_Rect srcRect = { 0, 0, w, h };
	SDL_Rect dstRect = { x, y, w, h };
	SDL_RenderCopyEx(RationalEngine::GetInstance()->GetRenderer(), m_TextureMap[id], &srcRect, &dstRect, 0, nullptr, flip);
}

void TextureManager::DrawFrame(std::string id, float x, float y, int w, int h, int row, int frame, SDL_RendererFlip flip)
{
	SDL_Rect srcRect = { w * frame, h * (row-1), w, h };
	SDL_Rect dstRect = { x, y, w , h };
	SDL_RenderCopyEx(RationalEngine::GetInstance()->GetRenderer(), m_TextureMap[id], &srcRect, &dstRect, 0, nullptr, flip);
}

void TextureManager::DrawTile(std::string tilesetId, int tileSize, float x, float y, int row, int frame, SDL_RendererFlip flip)
{
	SDL_Rect srcRect = { tileSize * frame, tileSize * row, tileSize, tileSize };
	SDL_Rect dstRect = { x , y , tileSize, tileSize };
	SDL_RenderCopyEx(RationalEngine::GetInstance()->GetRenderer(), m_TextureMap[tilesetId], &srcRect, &dstRect, 0, 0, flip);
}
