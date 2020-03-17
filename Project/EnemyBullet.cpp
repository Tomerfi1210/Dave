#include "EnemyBullet.h"
#include "ResourceManager.h"
#include "Factory.h"



EnemyBullet::EnemyBullet(sf::Vector2f& pos) : Bullets(pos)
{
	m_enemyBullet = ResourceManager::getInstance().getTexture(Enemy_Bullet_type);
	m_sprite.setTexture(*m_enemyBullet);
}

//---------------------------------------------------------------------------------------------
//registering the entity to map
bool EnemyBullet::m_registerit = Factory<Bullets>::registerit(Textures::Enemy_Bullet_c,
	[](sf::Vector2f& x) -> std::unique_ptr<Bullets> { return std::make_unique<EnemyBullet>(x); });