#include "Bertie.h"
#include "../Graphics/TextureManager.h"
#include <SDL.h>

Bertie::Bertie(Properties* props): Character(props)
{
	m_Row = 1;
	m_FrameCount = 8;
	m_AnimSpeed = 40;
	m_Frame = 0;
}

void Bertie::Draw()
{
	TextureManager::GetInstance()->DrawFrame(m_TextureID, m_Transform->X, m_Transform->Y, m_Width, m_Height, m_Scale, m_Row, m_Frame);
}

void Bertie::Update(float dt)
{
	m_Frame = (SDL_GetTicks() / m_AnimSpeed) % m_FrameCount;
	m_Transform->X += 1;
}

void Bertie::Clean()
{
	TextureManager::GetInstance()->Clean();
}
