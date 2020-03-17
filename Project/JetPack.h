#pragma once
#include "PowerUp.h"
class JetPack : public PowerUp
{
public:
	JetPack() = default;
	JetPack(sf::Vector2f&);
	~JetPack() = default;;
private:
	static bool m_registered;
};

