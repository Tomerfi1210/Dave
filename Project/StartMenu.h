#pragma once
#include"Menu.h"
class StartMenu : public Menu
{
public:
	StartMenu();
	~StartMenu() = default;
	void getInput(GameManager *manager);
	//to set pos
	virtual void setButPos();
	//to draw on screen
	void draw(sf::RenderWindow &window);
	//to select button
	butType_t selectedBut()const override;
};

