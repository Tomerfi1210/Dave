#include "PowerUp.h"
#include "ResourceManager.h"
#include <iostream>

PowerUp::PowerUp(sf::Vector2f & pos) : GameObject(pos)
{
	m_sheet.setPosition(pos.y * 60, pos.x * 60);
}


void PowerUp::draw(sf::RenderWindow &window)
{
	window.draw(m_sheet);
}