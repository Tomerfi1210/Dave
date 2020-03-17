#include "StraightMove.h"
#include "Dave.h"
#include "Bullets.h"

StraightMove::StraightMove(GameObject &obj) : object(&obj)
{
}

std::unique_ptr<MoveStrategy> StraightMove::move(GameObject &obj, sf::Vector2f &dir)
{
	if (typeid(obj) == typeid(Dave))
		m_speed = 7.f;
	static int i = 0;
	if (i >= 25) {
		i = 0;
		object->getSprite().move({ dir.x * m_speed, dir.y * m_speed });
	}
	i++;
	return nullptr;
}

void StraightMove::setDirection()
{
	static int m_walk = 0;
	if (m_timer.getElapsedTime().asSeconds() >= m_moveTimer.asSeconds())
	{
		m_timer.restart();
		m_walk++;
	}
	if (m_walk >= 3) {
		m_walk = 0;
	}

	sf::IntRect tmp(DYNAMIC_SIZE * m_walk, 0, DYNAMIC_SIZE, DYNAMIC_SIZE);
	object->getSprite().setTextureRect(tmp);
	m_step.x = { m_speed }; 
	
	m_dir = Right;
}
