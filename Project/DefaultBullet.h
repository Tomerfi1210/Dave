#pragma once
#include "Bullets.h"
class DefaultBullet : public Bullets
{
public:
	DefaultBullet() = default;
	DefaultBullet(sf::Vector2f & pos);
	~DefaultBullet() = default;
private:
	static bool m_registerit;
};

