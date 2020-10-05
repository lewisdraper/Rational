#pragma once
#include "../Object/GameObject.h"

class Character : public GameObject
{
public:
	Character(Properties* props): GameObject(props){}
	
	virtual void Draw() = 0;
	virtual void Update(float dt) = 0;
	virtual void Clean() = 0;

private:
	std::string m_Name;
};
