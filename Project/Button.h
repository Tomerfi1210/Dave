#pragma once
//===========================================include===========================
#include <SFML/Graphics.hpp> 
#include <string>

class Button
{
public:
	Button();
	//this c'tor sets the button place
	Button(sf::Vector2f pos);
	~Button();
	//this func draws the button to the window
	void draw(sf::RenderWindow &window);
	//this func sets the text of the button which is its name
	void setName(std::string name);
	//this func sets the postion of the button
	void setPos(sf::Vector2f pos);
	//this func return the position of the button
	sf::Vector2f getPos() const;
	//this func sets the button that its selected now
	void select();
	//this func sets the button that its not selected
	void unselect();
	//this func return true if the button is selected
	bool is_selected() const;
	//--------------------------private----------------------------
private:
	//the title of the button in the menu
	std::string m_name;
	//the button pos
	sf::Vector2f m_pos;

	bool m_selected;
	sf::Text m_text;
	sf::Font m_font;
};

