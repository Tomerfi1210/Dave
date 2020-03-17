#include "HorizontalEnemy.h"
#include "Factory.h"
#include "ResourceManager.h"
#include <iostream>
HorizontalEnemy::HorizontalEnemy(sf::Vector2f & pos)
	:Enemy(pos), m_dirc({ -0.7f,0 }), m_limit(100.f)
{
	m_texture = (ResourceManager::getInstance().getTexture(LineGuard_type));
	m_sprite.setTexture(*m_texture);
	m_sprite.setOrigin(sf::Vector2f{ DYNAMIC_SIZE / 2, DYNAMIC_SIZE / 2 });
	m_startPos = sf::Vector2f(m_sprite.getPosition().x, m_sprite.getPosition().y);
	m_moveTimer = sf::seconds(3.f);
}

void HorizontalEnemy::move(sf::Vector2f d)
{	
	static int i = 0;
	if (i >= 5) {
		sf::Vector2f currPos = m_sprite.getPosition();
		if (currPos.x + m_dirc.x < (m_startPos.x - m_limit) || //crossed from left
			currPos.x + m_dirc.x >(m_startPos.x + m_limit)) //crossed from right
			m_dirc.x = -m_dirc.x; //change the direction to right
		m_sprite.setPosition(sf::Vector2f(currPos.x + m_dirc.x, currPos.y + m_dirc.y));
		i = 0;
	}
	i++;
}

bool HorizontalEnemy::m_registered = Factory<Enemy>::registerit(Textures::Line_Guard_c,
	[](sf::Vector2f &place) -> std::unique_ptr<Enemy> { return std::make_unique<HorizontalEnemy>(place); });
