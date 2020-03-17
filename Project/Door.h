#pragma once
#include "UnMoveAble.h"
class Door : public UnMoveAble
{
public:
	Door() = default;
	Door(sf::Vector2f&);
	sf::FloatRect getRect();
	~Door() = default;

private:
	static bool m_registered;
};

