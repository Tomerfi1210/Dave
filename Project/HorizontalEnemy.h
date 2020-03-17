#pragma once
#include "Enemy.h"
class HorizontalEnemy : public Enemy
{
public:
	HorizontalEnemy() = default;
	~HorizontalEnemy() = default;
	HorizontalEnemy(sf::Vector2f &pos);
	virtual void move(sf::Vector2f d = { 0.f, 0.f }) override;
private:
	sf::Vector2f m_dirc;
	float m_limit;
	static bool m_registered;
	sf::Vector2f m_startPos;
};

