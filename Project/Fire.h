#pragma once
#include "UnMoveAble.h"
class Fire : public UnMoveAble
{
public:
	Fire() = default;
	Fire(sf::Vector2f&);
	~Fire() = default;
	void draw(sf::RenderWindow& window) override;
	sf::FloatRect getRect();
private:
	static bool m_registered;
};

