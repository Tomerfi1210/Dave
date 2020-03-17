#include "Wall.h"
#include "ResourceManager.h"
#include "Factory.h"



Wall::Wall(sf::Vector2f& pos) : UnMoveAble(pos)
{
	m_texture = ResourceManager::getInstance().getTexture(Wall_type);
	m_sprite.setTexture(*m_texture);
	m_sprite.setPosition({ pos.y * STATIC_SIZE, pos.x * STATIC_SIZE });
}

bool Wall::m_registered = Factory<UnMoveAble>::registerit(Textures::Wall_c,
	[](sf::Vector2f &place) -> std::unique_ptr<UnMoveAble> { return std::make_unique<Wall>(place); });