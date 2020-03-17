#pragma once
#include "GameObject.h"
class PowerUp : public GameObject
{
public:
	PowerUp() = default;
	PowerUp(sf::Vector2f& pos);
	virtual void draw(sf::RenderWindow & window);
	virtual ~PowerUp() = default;
	sf::FloatRect getRect()
	{
		auto tmp = m_sheet;
		tmp.setScale(0.7, 0.7);
		return tmp.getGlobalBounds();
	}
protected:
	sf::Sprite m_sheet;
	sf::Clock m_timer;
	float m_change;
	int m_transparency;
	sf::Sprite m_background;
};

