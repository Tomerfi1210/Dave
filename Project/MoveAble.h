#pragma once
#include "GameObject.h"



class MoveAble : public GameObject
{
public:
	MoveAble(sf::Vector2f& pos);
	MoveAble() = default;
	virtual ~MoveAble()  = default;
	virtual void move(sf::Vector2f = { 0.f, 0.f }) = 0;
	bool killed() const { return isKilled; }
	void setKill(const bool& kill) { isKilled = kill; }
protected:
	sf::Texture *m_explode = nullptr;
	sf::Clock m_clock;
	const float limitDead = 1.7f;
	bool isKilled = false;
};
