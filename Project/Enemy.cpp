#include "Enemy.h"
#include "Factory.h"

Enemy::Enemy(sf::Vector2f & pos) : MoveAble(pos)
{
	m_timer.restart();
}
