#pragma once
#include "Character.h"
#include "../Animation/Animation.h"

class Bertie : public Character
{
public:
	Bertie(Properties* props);
	virtual void Draw();
	virtual void Update(float dt);
	virtual void Clean();

private:
	Animation* m_Animation;
};