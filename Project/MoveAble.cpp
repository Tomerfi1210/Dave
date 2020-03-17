#include "MoveAble.h"
#include "ResourceManager.h"



MoveAble::MoveAble(sf::Vector2f & pos) : GameObject(pos)
{
	m_explode = ResourceManager::getInstance().getTexture(Explode_type);
}

