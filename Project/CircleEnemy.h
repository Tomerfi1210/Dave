#pragma once
#include "Enemy.h"
class CircleEnemy : public Enemy
{
public:
	CircleEnemy() = default;
	~CircleEnemy() = default;
	CircleEnemy(sf::Vector2f&);
	virtual void move(sf::Vector2f d = { 0.f, 0.f }) override;
private:
	static bool m_registered;
	const int m_radius;
	sf::Vector2f m_center;
};

