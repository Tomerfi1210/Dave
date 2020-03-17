#include "Bullets.h"
#include "Factory.h"
#include "ResourceManager.h"
#include "Keys.h"
#include "StraightMove.h"

Bullets::Bullets(sf::Vector2f &pos) : ChangeMove(pos)
{

	//m_sprite.setOrigin((sf::Vector2f)(m_sprite.getTexture()->getSize() / 2u));
//	m_sprite.setPosition({ pos.y * STATIC_SIZE + 10, pos.x * STATIC_SIZE + 10});
	setStrategy(std::make_unique<StraightMove>(*this));
	float speed = 30.f;
	m_move->setSpeed(speed);
}

void Bullets::setStrategy(std::unique_ptr<MoveStrategy> setMove)
{
	m_move = std::move(setMove);
}

void Bullets::move(sf::Vector2f pos)
{
	if (m_move)
	{
		auto p = m_move->move(*this, pos);

		if (p)
			m_move = std::move(p);
	}
}

