#pragma once
#include "UnMoveAble.h"
class Electricity : public UnMoveAble
{
public:
	Electricity() = default;
	Electricity(sf::Vector2f&);
	~Electricity() = default;
	void draw(sf::RenderWindow& window) override;
	sf::FloatRect getRect()
	{
		auto tmp = m_sprite;
		tmp.setScale(0.7f, 0.7f);
		return tmp.getGlobalBounds();
	}

private:
	static bool m_registered;
};

