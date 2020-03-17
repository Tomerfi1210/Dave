#pragma once
#include "PowerUp.h"
class Gun : public PowerUp
{
public:
	Gun() = default;
	Gun(sf::Vector2f&);
	~Gun() = default;
private:
	static bool m_registered;
};

