#include "Fire.h"
#include "Factory.h"
#include "ResourceManager.h"



Fire::Fire(sf::Vector2f &pos) : UnMoveAble(pos)
{
	m_texture = ResourceManager::getInstance().getTexture(Fire_type);
	m_sprite.setTexture(*m_texture);
	m_sprite.setPosition({ pos.y * STATIC_SIZE, pos.x * STATIC_SIZE });
	//m_sprite.setOrigin(sf::Vector2f{ STATIC_SIZE / 2, STATIC_SIZE / 2 });
	m_sprite.move({ 5,6 });
}

void Fire::draw(sf::RenderWindow & window)
{
	m_animation.show(window, m_sprite, DYNAMIC_SIZE);
}


sf::FloatRect Fire::getRect()
{
	auto tmp = m_sprite;
	tmp.setScale(0.7, 0.7);
	return tmp.getGlobalBounds();
}

bool Fire::m_registered = Factory<UnMoveAble>::registerit(Textures::Fire_c,
	[](sf::Vector2f &place) -> std::unique_ptr<UnMoveAble> { return std::make_unique<Fire>(place); });