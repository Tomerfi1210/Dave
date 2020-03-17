#pragma once
#include "MoveStrategy.h"
class Dave;
class PlayerMove : public MoveStrategy
{
public:
	PlayerMove(Dave&);
	~PlayerMove() = default;
	std::unique_ptr<MoveStrategy> move(GameObject&, sf::Vector2f&) override;
	void setDirection();
	
private:
	std::map<sf::Keyboard::Key, std::function<void(void)>> m_moves;//holds direction of the robot.
	bool m_moveHands;
	Dave& m_dave;
	int m_walk = 0;
};

