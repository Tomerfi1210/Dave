#pragma once
#include "UnMoveAble.h"
class Rock :public UnMoveAble
{
public:
	Rock() = default;
	Rock(sf::Vector2f&);
	~Rock() = default;
private:
	static bool m_registered;
};

