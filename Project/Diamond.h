#pragma once
#include "PowerUp.h"
class Diamond : public PowerUp
{
public:
	Diamond() = default;
	Diamond(sf::Vector2f&);
	~Diamond() = default;
private:
	static bool m_registered;
};

