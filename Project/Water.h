#pragma once
#include "UnMoveAble.h"
class Water : public UnMoveAble
{
public:
	Water(sf::Vector2f&);
	Water() = default;
	~Water() = default;
	void draw(sf::RenderWindow& window) override;
	sf::FloatRect getRect()
	{
		auto tmp = m_sprite;
		tmp.setScale(0.7, 0.7);
		return tmp.getGlobalBounds();
	}
private:
	static bool m_registered;
};

