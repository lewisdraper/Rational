#include "Bertie.h"
#include "../Graphics/TextureManager.h"
#include "../Events/EventHandler.h"
#include "../Collision/CollisionHandler.h"

#include <SDL.h>

Bertie::Bertie(Properties* props): Character(props)
{
	m_JumpForce = JUMP_FORCE;
	m_JumpTime = JUMP_TIME;
	m_Collision = new CollisionBox();
	m_Collision->SetBuffer(-15, -25, 18, 43);

	m_RigidBody = new RigidBody();
	//m_RigidBody->SetGravity(5.0f);

	m_Animation = new Animation();
	m_Animation->SetProps(m_TextureID, 1, 8, 90);


}

void Bertie::Draw(float scale)
{
	m_Animation->Draw(m_Transform->X, m_Transform->Y, m_Width, m_Height, scale);
	//m_Collision->Draw();
}

void Bertie::Update(float dt)
{

	m_Animation->SetProps("bertIdle", 1, 8, 80, m_Animation->GetFlip());
	m_RigidBody->UnsetForce();

	if (EventHandler::GetInstance()->GetKeyDown(SDL_SCANCODE_D) || EventHandler::GetInstance()->GetKeyDown(SDL_SCANCODE_RIGHT))
	{
		m_Animation->SetProps("bertWalking", 1, 8, 80);
		m_RigidBody->ApplyForceX(10);
	}
	if (EventHandler::GetInstance()->GetKeyDown(SDL_SCANCODE_A) || EventHandler::GetInstance()->GetKeyDown(SDL_SCANCODE_LEFT))
	{
		m_Animation->SetProps("bertWalking", 1, 8, 80, SDL_FLIP_HORIZONTAL);
		m_RigidBody->ApplyForceX(-10);
	}

	//jump
	if (EventHandler::GetInstance()->GetKeyDown(SDL_SCANCODE_SPACE) && m_IsGrounded)
	{
		m_IsJumping = true;
		m_IsGrounded = false;
		m_RigidBody->ApplyForceY(m_JumpForce);
	}
	if (EventHandler::GetInstance()->GetKeyDown(SDL_SCANCODE_SPACE) && m_IsJumping && m_JumpTime > 0)
	{
		m_JumpTime -= dt;
		m_RigidBody->ApplyForceY(m_JumpForce);
	}
	else
	{
		m_IsJumping = false;
		m_JumpTime = JUMP_TIME;
	}
	m_RigidBody->Update(dt);

	//move on X axis
	m_LastSafePosition.X = m_Transform->X;
	m_Transform->TranslateX(m_RigidBody->GetPosition().X);

	//check collision on X axis
	m_Collision->Set(m_Transform->X, m_Transform->Y, 64, 64);
	if (CollisionHandler::GetInstance()->MapCollision(m_Collision->Get()))
		m_Transform->X = m_LastSafePosition.X;

	m_RigidBody->Update(dt);

	//move on Y axis
	m_LastSafePosition.Y = m_Transform->Y;
	m_Transform->TranslateY(m_RigidBody->GetPosition().Y);
	m_Collision->Set(m_Transform->X, m_Transform->Y, 64, 64);

	if (CollisionHandler::GetInstance()->MapCollision(m_Collision->Get()))
	{
		m_Transform->Y = m_LastSafePosition.Y;
		m_IsGrounded = true;
	}
	else
	{
		m_IsGrounded = false;
	}

	if (m_IsJumping || !m_IsGrounded)
	{
		m_Animation->SetProps("bertJump", 1, 14, 150, m_Animation->GetFlip());
	}


	m_Origin->X = m_Transform->X + m_Width / 2;
	m_Origin->Y = m_Transform->Y + m_Height / 2;

	m_Animation->Update();

}

void Bertie::Clean()
{
	TextureManager::GetInstance()->Drop(m_TextureID);
}
