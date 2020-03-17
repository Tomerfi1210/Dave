#include "PlayerMove.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Dave.h"
#include <iostream>
//TODO move from here
static int count = 0;
PlayerMove::PlayerMove(Dave& dave) : m_moveHands(false), m_dave(dave)
{
	m_speed = 0.7f;
	m_moves.emplace(sf::Keyboard::Right, [&]() {m_step.x = { m_speed }; m_dave.getSprite().setScale({ 1,1 }); m_dir = Right; });
	m_moves.emplace(sf::Keyboard::Left, [&]() {m_step.x = { -m_speed }; m_dave.getSprite().setScale({ -1,1 }); m_dir = Left; });
	m_moves.emplace(sf::Keyboard::Up, [&]() {if (!m_can_jump && !m_can_fly || m_step.y != 0) return; m_can_jump = false; if (m_can_fly) m_can_jump = true; m_step.y = { -m_speed }; count++;
	if (m_dir == Right)m_dave.getSprite().setScale({ 1,1 }); else m_dave.getSprite().setScale({ -1,1 }); });
	m_moves.emplace(sf::Keyboard::Down, [&]() {if (!m_can_fly) return; m_step.y = { m_speed }; m_dave.getSprite().setScale({ 1,1 }); });
}
//------------------------------------------------------------------------------------
std::unique_ptr<MoveStrategy> PlayerMove::move(GameObject& player, sf::Vector2f&)
{
	if (m_can_fly) {
		sf::IntRect tmp(0, 0, DYNAMIC_SIZE, DYNAMIC_SIZE);
		m_dave.getSprite().setTextureRect(tmp);
	}
	else {
		if (m_timer.getElapsedTime().asSeconds() >= m_moveTimer.asSeconds() && m_moveHands)
		{
			m_timer.restart();
			m_walk++;
		}
		if (m_walk >= 3) {
			m_walk = 0;
		}

		if (m_step.y == 0) {
			sf::IntRect tmp(DYNAMIC_SIZE * m_walk, 0, DYNAMIC_SIZE, DYNAMIC_SIZE);
			m_dave.getSprite().setTextureRect(tmp);
		}
	}

	m_dave.getSprite().move(m_step);
	m_step.x = { 0 };
	return nullptr;
}
//----------------------------------------------------------------------------------------
void PlayerMove::setDirection()
{
	bool isPressed = false;
	for (const auto &cell : m_moves)
	{
		if (sf::Keyboard::isKeyPressed(cell.first))
		{
			cell.second();
			m_moveHands = true;
			isPressed = true;
		}
	}
	if(!isPressed)
		m_moveHands = false;

	static int jetCountUp = 0;
	static int jetCountDown = 0;
	if (m_can_fly)
	{
		if (m_step.y < 0) {
			jetCountUp++;

			if (jetCountUp >= 70)
			{
				jetCountUp = 0;
				m_step.y = 0;
			}
		}
		else if (m_step.y > 0) {
			jetCountDown++;

			if (jetCountDown >= 70)
			{
				jetCountDown = 0;
				m_step.y = 0;
			}
		}
		return;
	}
	//adding the movement upwards to the counter
	if (m_step.y < 0)
		count++;
	//TODO, make this 200 an attribute(data member)

	if (count >= 270)
	{
		count = 0;
		//keep it true for going downwards
		m_step = { 0, m_speed };//make him go back down
		m_can_jump = false;
	}
	/*if (count <= 0)
		m_jumping = false;*/
}
