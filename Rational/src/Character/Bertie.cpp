#include "Bertie.h"
#include "../Graphics/TextureManager.h"

#include <SDL.h>

Bertie::Bertie(Properties* props): Character(props)
{
	m_Animation = new Animation();
	m_Animation->SetProps(m_TextureID, 1, 8, 80);
}

void Bertie::Draw()
{
	m_Animation->Draw(m_Transform->X, m_Transform->Y, m_Width, m_Height);
}

void Bertie::Update(float dt)
{
	m_Transform->X += 1;
	m_Animation->Update();
}

void Bertie::Clean()
{
	TextureManager::GetInstance()->Clean();
}
