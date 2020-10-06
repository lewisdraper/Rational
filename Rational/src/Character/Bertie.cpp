#include "Bertie.h"
#include "../Graphics/TextureManager.h"
#include "../Events/EventHandler.h"

#include <SDL.h>

Bertie::Bertie(Properties* props): Character(props)
{
	m_Animation = new Animation();
	m_Animation->SetProps(m_TextureID, 1, 8, 80);
	m_RigidBody = new RigidBody();
}

void Bertie::Draw()
{
	m_Animation->Draw(m_Transform->X, m_Transform->Y, m_Width, m_Height);
}

void Bertie::Update(float dt)
{
	m_Animation->SetProps("bertIdle", 1, 8, 80, m_Animation->GetFlip());
	m_RigidBody->UnsetForce();

	if (EventHandler::GetInstance()->GetKeyDown(SDL_SCANCODE_D))
	{
		m_Animation->SetProps("bertWalking", 1, 8, 80);
		m_RigidBody->ApplyForceX(5);
	}
	if (EventHandler::GetInstance()->GetKeyDown(SDL_SCANCODE_A))
	{
		m_Animation->SetProps("bertWalking", 1, 8, 80, SDL_FLIP_HORIZONTAL);
		m_RigidBody->ApplyForceX(-5);
	}

	m_RigidBody->Update(0.6);
	m_Transform->TranslateX(m_RigidBody->GetPosition().X);
	//m_Transform->TranslateY(m_RigidBody->GetPosition().Y);
	m_Animation->Update();

}

void Bertie::Clean()
{
	TextureManager::GetInstance()->Clean();
}
