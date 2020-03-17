#include "Electricity.h"
#include "Factory.h"
#include "ResourceManager.h"

Electricity::Electricity(sf::Vector2f &pos) : UnMoveAble(pos)
{
	m_texture = ResourceManager::getInstance().getTexture(Electricity_type);
	m_sprite.setTexture(*m_texture);
	m_sprite.setPosition({ pos.y * STATIC_SIZE, pos.x * STATIC_SIZE });
	m_sprite.move({ 5,6 });
}

void Electricity::draw(sf::RenderWindow & window)
{
	m_animation.show(window, m_sprite, DYNAMIC_SIZE);
}


bool Electricity::m_registered = Factory<UnMoveAble>::registerit(Textures::Electricity_c,
	[](sf::Vector2f &place) -> std::unique_ptr<UnMoveAble> { return std::make_unique<Electricity>(place); });