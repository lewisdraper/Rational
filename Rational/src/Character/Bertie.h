#pragma once
#include "Character.h"
#include "../Animation/Animation.h"
#include "../Physics/RigidBody.h"

class Bertie : public Character
{
public:
	Bertie(Properties* props);
	virtual void Draw(float scale=1);
	virtual void Update(float dt);
	virtual void Clean();

private:
	Animation* m_Animation;
	RigidBody* m_RigidBody;
};