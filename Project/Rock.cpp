#include "Rock.h"
#include "ResourceManager.h"
#include "Factory.h"

Rock::Rock(sf::Vector2f &pos)
{
	m_texture = ResourceManager::getInstance().getTexture(Rock_type);
	m_sprite.setTexture(*m_texture);
	m_sprite.setPosition({ pos.y * STATIC_SIZE, pos.x * STATIC_SIZE });
}
bool Rock::m_registered = Factory<UnMoveAble>::registerit(Textures::Rock_c,
	[](sf::Vector2f &place) -> std::unique_ptr<UnMoveAble> { return std::make_unique<Rock>(place); });