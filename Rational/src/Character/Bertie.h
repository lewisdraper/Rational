#pragma once
#include "Character.h"
#include "../Animation/Animation.h"
#include "../Physics/RigidBody.h"
#include "../Collision/CollisionBox.h"

#define JUMP_TIME 15.0f
#define JUMP_FORCE -20.0f

class Bertie : public Character
{
public:
	Bertie(Properties* props);
	virtual void Draw(float scale=1);
	virtual void Update(float dt);
	virtual void Clean();

private:
	bool m_IsGrounded, m_IsJumping;
	float m_JumpForce, m_JumpTime;

	Animation* m_Animation;
	RigidBody* m_RigidBody;
	CollisionBox* m_Collision;
	Vector2D m_LastSafePosition;
};