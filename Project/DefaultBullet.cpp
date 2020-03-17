#include "DefaultBullet.h"
#include "Factory.h"
#include "ResourceManager.h"



DefaultBullet::DefaultBullet(sf::Vector2f& pos) : Bullets(pos)
{
	m_texture = ResourceManager::getInstance().getTexture(Bullet_type);
	m_sprite.setTexture(*m_texture);
}

//---------------------------------------------------------------------------------------------
//registering the entity to map
bool DefaultBullet::m_registerit = Factory<Bullets>::registerit(Textures::Default_Bullet_c,
	[](sf::Vector2f& x) -> std::unique_ptr<Bullets> { return std::make_unique<DefaultBullet>(x); });