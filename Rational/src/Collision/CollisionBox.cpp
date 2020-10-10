#include "CollisionBox.h"
#include "../Camera/Camera.h"


void CollisionBox::Draw()
{
	Vector2D cam = Camera::GetInstance()->GetPosition();
	m_Box.x -= cam.X;
	m_Box.y -= cam.Y;
	SDL_RenderDrawRectF(RationalEngine::GetInstance()->GetRenderer(), &m_Box);
}
