#include "GameObject.h"

void GameObject::UpdateInfo()
{
	m_pos = { m_world._41,m_world._42,m_world._43 };
	m_dir = { m_world._31,m_world._32,m_world._33 };
	m_beforePos = m_pos;
}