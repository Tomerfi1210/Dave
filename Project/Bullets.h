#pragma once
#include "ChangeMove.h"
class Bullets : public ChangeMove
{
public:
	Bullets(sf::Vector2f&);
	Bullets() = default;
	virtual void setStrategy(std::unique_ptr<MoveStrategy>);
	virtual ~Bullets() = default;
	void move(sf::Vector2f = { 0.f, 0.f }) override;
};