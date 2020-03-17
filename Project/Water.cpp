#include "Water.h"
#include "Factory.h"
#include "ResourceManager.h"



Water::Water(sf::Vector2f &pos) : UnMoveAble(pos)
{
	m_texture = ResourceManager::getInstance().getTexture(Water_type);
	m_sprite.setTexture(*m_texture);
	m_sprite.setPosition({ pos.y * STATIC_SIZE, pos.x * STATIC_SIZE });
	m_sprite.move({ 5,6 });
}

void Water::draw(sf::RenderWindow & window)
{
	m_animation.show(window, m_sprite, DYNAMIC_SIZE);
}


bool Water::m_registered = Factory<UnMoveAble>::registerit(Textures::Water_c,
	[](sf::Vector2f &place) -> std::unique_ptr<UnMoveAble> { return std::make_unique<Water>(place); });