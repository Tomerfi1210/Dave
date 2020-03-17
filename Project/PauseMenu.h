#pragma once
#include "Menu.h"
#include <string>
class PauseMenu : public Menu
{
public:
	PauseMenu();
	~PauseMenu();
	void getInput(GameManager * manager);
	//returns the selected button
	butType_t selectedBut()const override;
	//to draw the menu
	void draw(sf::RenderWindow &window);
	//sets the pos of the buttons
	virtual void setButPos() override;
	bool askWindow(std::string str);
};

