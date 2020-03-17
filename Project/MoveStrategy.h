#pragma once
#include <memory>
#include <SFML\Graphics.hpp>
#include "Keys.h"
#include <map>
#include <functional>

class GameObject;

class MoveStrategy
{
public:
	MoveStrategy() = default;
	virtual ~MoveStrategy() = default;
	virtual std::unique_ptr<MoveStrategy> move(GameObject&, sf::Vector2f&) = 0;
	virtual void setDirection() = 0;
	sf::Vector2f& getStep() { return m_step; };
	bool getJump() const { return m_can_jump; }
	void setJump(const bool& jump) { m_can_jump = jump; }
	Direction_t getDir() const { return m_dir; }
	void setCanFly(const bool& fly) { m_can_fly = fly; }
	bool isFly() const { return m_can_fly; }
	void setSpeed(const float& speed) { m_speed = speed; }
protected:
	sf::Vector2f m_step;
	bool m_can_jump = false;
	bool m_can_fly = false;
	bool isCenter = false;
	Direction_t m_dir = Right;
	float m_speed;
	sf::Time m_moveTimer = sf::seconds(0.2f);
	sf::Clock m_timer;
};

