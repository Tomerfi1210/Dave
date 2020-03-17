#include "CircleEnemy.h"
#include "Factory.h"
#include "ResourceManager.h"
CircleEnemy::CircleEnemy(sf::Vector2f &pos)
	:Enemy(pos), m_radius(50)
{
	m_texture = (ResourceManager::getInstance().getTexture(CircleGuard_type));
	m_sprite.setTexture(*m_texture);
	m_sprite.setOrigin(sf::Vector2f{ DYNAMIC_SIZE / 2, DYNAMIC_SIZE / 2 });

	m_center.x = m_sprite.getPosition().x;
	m_center.y = (m_sprite.getPosition().y + m_radius);
}
void CircleEnemy::move(sf::Vector2f d)
{
	static int i = 0;
	if (i >= 4) 
	{
			static float m_angle = 0.f;
		m_angle += 0.01f;
		float x = m_center.x + cos(m_angle)*m_radius;
		float y = m_center.y + sin(m_angle)*m_radius;
	//if no collision
	
		i = 0;
		m_sprite.setPosition(x, y);
	}
	i++;
}

bool CircleEnemy::m_registered = Factory<Enemy>::registerit(Textures::Circle_Guard_c,
	[](sf::Vector2f &place) -> std::unique_ptr<Enemy> { return std::make_unique<CircleEnemy>(place); });
