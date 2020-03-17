#pragma once
#include "Bullets.h"
class EnemyBullet : public Bullets
{
public:
	EnemyBullet() = default;
	EnemyBullet(sf::Vector2f&);
	~EnemyBullet() = default;
	void draw(sf::RenderWindow& window)
	{
		window.draw(m_sprite); 
	}
private:
	sf::Texture *m_enemyBullet = nullptr;
	static bool m_registerit;
};

