#include "Diamond.h"
#include "Factory.h"
#include "ResourceManager.h"

Diamond::Diamond(sf::Vector2f &pos) :PowerUp(pos)
{
	m_texture = (ResourceManager::getInstance().getTexture(Gifts_type));
	m_sheet.setTexture(*m_texture);
	m_sheet.setOrigin(sf::Vector2f{ DYNAMIC_SIZE / 2, DYNAMIC_SIZE / 2 });
	m_sheet.move(DYNAMIC_SIZE / 2, DYNAMIC_SIZE / 2);
}
bool Diamond::m_registered = Factory<PowerUp>::registerit(Textures::Gift_c,
	[](sf::Vector2f &place) -> std::unique_ptr<PowerUp> { return std::make_unique<Diamond>(place); });