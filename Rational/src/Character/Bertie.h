#pragma once
#include "Character.h"

class Bertie : public Character
{
public:
	Bertie(Properties* props);
	virtual void Draw();
	virtual void Update(float dt);
	virtual void Clean();

private:
	int m_Row, m_Frame, m_FrameCount;
	int m_AnimSpeed;
};