#pragma once
#include <string>
#include <SDL.h>

#pragma warning( push )
#pragma warning( disable : 26812)
class Animation
{
public:
	Animation() {};
	void Update();
	void Draw(float x, float y, int spriteWidth, int spriteHeight, float scale=1);
	void SetProps(std::string textureID, int spriteRow, int frameCount, int animSpeed, SDL_RendererFlip flip = SDL_FLIP_NONE);
	inline SDL_RendererFlip GetFlip() { return m_Flip; }

private:
	int m_SpriteRow = 0, m_SpriteFrame = 0;
	int m_AnimSpeed = 0, m_FrameCount = 0;
	std::string m_TextureID = "";
	SDL_RendererFlip m_Flip = SDL_FLIP_NONE;

};
#pragma warning( pop ) 
