#pragma once
//===========================================include===========================
#include "Button.h"
#include <SFML/Graphics.hpp> 
#include <vector>
#include "string"
#include "Keys.h"
#include "Sound.h"
//=============================================================================
class GameManager;
class Menu
{
public:
	Menu();
	//to set the button position
	virtual void setButPos() = 0;
	//to draw on the window
	void draw(sf::RenderWindow &window);
	//to set the picked button
	bool pickButton(Sound &sound);
	//to fix the sound text
	void SetSoundString(bool mute);
	//to move up in the menu
	void SelectUp();
	//to move down in the menu
	void SelectDown();
	//returns the selected button
	virtual butType_t selectedBut()const = 0;
	//add a new button to the menu
	void addButton(std::string name);
	~Menu();
protected:
	int m_selected;
	std::vector<std::unique_ptr<Button>> m_button;
	sf::Texture m_backGround;
	sf::Sprite m_backPic;
	GameManager * m_manager;
};

