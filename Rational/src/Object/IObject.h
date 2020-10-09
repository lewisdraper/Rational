#pragma once
class IObject
{
public:
	virtual void Draw(float scale) = 0;
	virtual void Update(float dt) = 0;
	virtual void Clean() = 0;
};