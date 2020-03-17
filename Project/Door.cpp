#include "Door.h"
#include "ResourceManager.h"
#include "Factory.h"

Door::Door(sf::Vector2f &pos) : UnMoveAble(pos)
{
	m_texture = ResourceManager::getInstance().getTexture(Door_type);
	m_sprite.setTexture(*m_texture);
	m_sprite.setPosition({ pos.y * STATIC_SIZE, pos.x * STATIC_SIZE });
}

sf::FloatRect Door::getRect()
{
	auto tmp = m_sprite;
	tmp.setScale(0.7, 0.7);
	return tmp.getGlobalBounds();
}

bool Door::m_registered = Factory<UnMoveAble>::registerit(Textures::Door_c,
	[](sf::Vector2f &place) -> std::unique_ptr<UnMoveAble> { return std::make_unique<Door>(place); });