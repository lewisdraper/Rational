#pragma once
#include <SDL.h>
class CollisionBox
{
public:
	inline SDL_FRect Get() { return m_Box; }
	inline void SetBuffer(float x, float y, float w, float h) { m_Buffer = { x, y, w, h }; }

	void Set(float x, float y, float w, float h)
	{
		m_Box = {
			x - m_Buffer.x,
			y - m_Buffer.y,
			w - m_Buffer.w,
			h - m_Buffer.h
		};
	}
	void Draw();

private:
	SDL_FRect m_Box;
	SDL_FRect m_Buffer;

};