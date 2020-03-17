#pragma once
#include "MoveAble.h"
class ChangeMove : public MoveAble
{
public:
	ChangeMove() = default;
	ChangeMove(sf::Vector2f&);
	virtual ~ChangeMove() = default;
	virtual void setStrategy(std::unique_ptr<MoveStrategy>) = 0;
	std::unique_ptr<MoveStrategy>& getStrategy() { return m_move; }

protected:
	std::unique_ptr<MoveStrategy>m_move;
};

