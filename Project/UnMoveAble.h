#pragma once
#include "GameObject.h"
class UnMoveAble : public GameObject
{
public:
	UnMoveAble(sf::Vector2f& pos);
	UnMoveAble();
	virtual ~UnMoveAble();
};

