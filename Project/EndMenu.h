#pragma once
#include "Menu.h"
class EndMenu : public Menu
{
public:
	EndMenu();
	~EndMenu();
	void getInput(GameManager *manager);
	EndMenu(bool win, int score);
	//this func sets the position of the buttons on the screen
	virtual void setButPos()override;
	//to draw the button on the screen
	void draw(sf::RenderWindow &window);
	//this func return the selected button
	butType_t selectedBut()const override;
	//-----------------------------private----------------------------
private:
	bool m_won;
	int m_score;
	sf::Text m_scoreText;
	sf::Texture m_endTx;
	sf::Sprite m_endSp;
};

