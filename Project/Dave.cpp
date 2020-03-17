#include "Dave.h"
#include "PlayerMove.h"
#include "ResourceManager.h"
#include "StraightMove.h"


Dave::Dave(sf::Vector2f & startpos) : ChangeMove(startpos), m_life(3)
{
	m_texture = (ResourceManager::getInstance().getTexture(Dave_Regular_type));
	m_sprite.setTexture(*m_texture);//Regulare dave.

	m_Jet = (ResourceManager::getInstance().getTexture(Dave_JetPack_type));//Dave with jet.

	m_sprite.setOrigin(sf::Vector2f{ DYNAMIC_SIZE / 2, DYNAMIC_SIZE / 2 });
	m_sprite.move(DYNAMIC_SIZE / 2,DYNAMIC_SIZE/2);

	setStrategy(std::make_unique<PlayerMove>(*this));
}


void Dave::setStrategy(std::unique_ptr<MoveStrategy> setMove)
{
	m_move = std::move(setMove);
}

void Dave::draw(sf::RenderWindow & window)
{
	if (m_straight)
	{
		m_sprite.setScale({ 1, 1 });
		m_animation.show(window, m_sprite, DYNAMIC_SIZE);
		return;
	}
	if (m_move->isFly() && !killed())
		m_sprite.setTexture(*m_Jet);

	else if(!m_move->isFly() && !killed())
		m_sprite.setTexture(*m_texture);

	else {
		m_sprite.setTexture(*m_explode);
		m_animation.show(window, m_sprite, DYNAMIC_SIZE);
		return;
	}
	window.draw(m_sprite);
}

void Dave::setInfo(GameInfo * info)
{
	m_info = info;
}

void Dave::addScore()
{
	m_info->updateScore(m_info->getScore() + 5);
}


void Dave::directionSet()
{
	m_move->setDirection();
}

void Dave::move(sf::Vector2f d)
{

	sf::Vector2f dir = { 1, 0 };
	if (m_move)
	{
		m_move->setSpeed(speed);
		auto p = m_move->move(*this, dir);

		if (p)
			m_move = std::move(p);
	}
}

sf::FloatRect Dave::getRect()
{
	auto tmp = m_sprite;
	tmp.move(m_move->getStep());
	return tmp.getGlobalBounds();
}

