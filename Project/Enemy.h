#pragma once
#include "MoveAble.h"
#include "UnMoveAble.h"

class Enemy : public MoveAble
{
public:
	Enemy(sf::Vector2f& pos);
	Enemy() = default;
	virtual ~Enemy() = default;
	virtual void move(sf::Vector2f d = { 0.f, 0.f }) = 0;
	void draw(sf::RenderWindow & window)
	{
		if (killed())
			m_sprite.setTexture(*m_explode);
		else
			m_sprite.setTexture(*m_texture);

		m_animation.show(window, m_sprite, 50);
	}
	void resetClock() { m_timer.restart(); }
	void resetClockDie() { m_clock.restart();}
	bool TimeLimit() const { return m_timer.getElapsedTime().asSeconds() >= m_moveTimer.asSeconds(); }
	bool TimeToDie() const { return m_clock.getElapsedTime().asSeconds() >= m_die.asSeconds(); }

protected:
	sf::Time m_moveTimer = sf::seconds(2.5f);
	sf::Clock m_timer;
	sf::Clock m_clock;
	sf::Time m_die = sf::seconds(0.8f);
};