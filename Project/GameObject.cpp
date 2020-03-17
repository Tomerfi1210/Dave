#include "GameObject.h"



GameObject::GameObject(sf::Vector2f & pos) : m_startLocation(pos)
{
	m_sprite.setPosition({ m_startLocation.y * STATIC_SIZE, m_startLocation.x * STATIC_SIZE });
}

GameObject::GameObject()
{
}

void GameObject::draw(sf::RenderWindow & window)
{
	m_sprite.setTexture(*m_texture);
	window.draw(m_sprite);
}

void GameObject::resetPos()
{
	m_sprite.setPosition({ m_startLocation.y * STATIC_SIZE, m_startLocation.x * STATIC_SIZE });
}

GameObject::~GameObject()
{
}
