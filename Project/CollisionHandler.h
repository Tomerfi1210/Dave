#pragma once
#include "GameObject.h"
#include <iostream>
struct UnknownCollision
{
	UnknownCollision(GameObject& a, GameObject& b) : first(a), second(b)
	{
		std::cout << "Unknown collision of " << typeid(a).name() << " and "
			<< typeid(b).name() << std::endl;
	}
	GameObject& first;
	GameObject& second;
};
bool isCollision(const sf::FloatRect&, const sf::FloatRect&);
void processCollision(GameObject& object1, GameObject& object2);