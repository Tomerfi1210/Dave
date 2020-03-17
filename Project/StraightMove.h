#pragma once
#include "MoveStrategy.h"
//bullet and dave use.
class StraightMove : public MoveStrategy
{
public:
	StraightMove() = default;
	StraightMove(GameObject&);
	~StraightMove() = default;
	virtual std::unique_ptr<MoveStrategy> move(GameObject&, sf::Vector2f&);
	virtual void setDirection() override;
private:
	GameObject *object;
};

