#pragma once
#include <SFML/Graphics.hpp>

class Animation
{
public:
	Animation();
	~Animation() = default;
	void show(sf::RenderWindow& window, sf::Sprite&, int);
protected:
	sf::Clock m_clock;
	sf::Time m_moveTimer = sf::seconds(0.6f);
};
