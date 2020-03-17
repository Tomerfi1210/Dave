#pragma once
#include "UnMoveAble.h"
class Wall : public UnMoveAble
{
public:
	Wall(sf::Vector2f&);
	~Wall() = default;
private:
	static bool m_registered;
};

