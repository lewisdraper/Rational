#include "Camera.h"

Camera* Camera::s_Instance = nullptr;

void Camera::Update(float dt) 
{
	if (m_Target != nullptr)
	{
		m_ViewBox.x = m_Target->X - WINDOW_WIDTH / 2;
		//m_ViewBox.y = m_Target->Y - WINDOW_HEIGHT / 2;

		if (m_ViewBox.x < 0)
			m_ViewBox.x = 0;

		if (m_ViewBox.y < 0)
			m_ViewBox.y = 0;

		if (m_ViewBox.x > (2 * WINDOW_WIDTH - m_ViewBox.w))
			m_ViewBox.x = (2 * WINDOW_WIDTH - m_ViewBox.w);

		if (m_ViewBox.y > (2 * WINDOW_HEIGHT - m_ViewBox.h))
			m_ViewBox.y = (2 * WINDOW_HEIGHT - m_ViewBox.h);

		m_Position = Vector2D(m_ViewBox.x, m_ViewBox.y);

	}
	
}
