#include "JetPack.h"
#include "Factory.h"
#include "ResourceManager.h"

JetPack::JetPack(sf::Vector2f &pos) : PowerUp(pos)
{
	m_texture = (ResourceManager::getInstance().getTexture(JetPack_type));
	m_sheet.setTexture(*m_texture);
	m_sheet.setOrigin(sf::Vector2f{ DYNAMIC_SIZE / 2, DYNAMIC_SIZE / 2 });
	m_sheet.move(DYNAMIC_SIZE / 2, DYNAMIC_SIZE / 2);
}


bool JetPack::m_registered = Factory<PowerUp>::registerit(Textures::Jet_Pack_c,
	[](sf::Vector2f &place) -> std::unique_ptr<PowerUp> { return std::make_unique<JetPack>(place); });