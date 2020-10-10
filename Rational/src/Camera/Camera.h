#pragma once
#include "../Physics/Point.h"
#include "../Physics/Vector2D.h"
#include "../Core/RationalEngine.h"
#include <SDL.h>

class Camera
{
public:
	static Camera* GetInstance() { return s_Instance = (s_Instance != nullptr) ? s_Instance : new Camera(); }
	inline SDL_FRect GetViewBox() { return m_ViewBox; }
	inline Vector2D GetPosition() { return m_Position; }
	inline void SetTarget(Point* target) { m_Target = target; }
	void Update(float dt);

protected:

private:
	Camera() 
	{
		m_ViewBox = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};
	};
	Point* m_Target;
	Vector2D m_Position;
	SDL_FRect m_ViewBox;

	static Camera* s_Instance;



};

