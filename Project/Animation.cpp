#include "Animation.h"
#include <iostream>

Animation::Animation()
{
	m_clock.restart();
}

void Animation::show(sf::RenderWindow & window, sf::Sprite &sprite, int size)
{
	static int counter = 0;
	if (m_clock.getElapsedTime().asSeconds() >= m_moveTimer.asSeconds())
	{
		m_clock.restart();
		counter++;
	}
	

	sf::IntRect tmp(size * (counter/3), 0, size, size);
	sprite.setTextureRect(tmp);
	window.draw(sprite);
	if (counter / 3 >= 3) counter = 0;
}
