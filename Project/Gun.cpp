#include "Gun.h"
#include "Factory.h"
#include "ResourceManager.h"

Gun::Gun(sf::Vector2f &pos) : PowerUp(pos)
{
	m_texture = (ResourceManager::getInstance().getTexture(Gun_type));
	m_sheet.setTexture(*m_texture);
	m_sheet.setOrigin(sf::Vector2f{ DYNAMIC_SIZE / 2, DYNAMIC_SIZE / 2 });
	m_sheet.move(DYNAMIC_SIZE / 2, DYNAMIC_SIZE / 2);
}
   

bool Gun::m_registered = Factory<PowerUp>::registerit(Textures::Gun_c,
	[](sf::Vector2f &place) -> std::unique_ptr<PowerUp> { return std::make_unique<Gun>(place); });
