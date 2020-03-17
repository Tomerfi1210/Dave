#include "Button.h"



Button::Button()
	:m_selected(false)
{
}

void Button::draw(sf::RenderWindow & window)
{
	m_font.loadFromFile("GOUDYSTO.TTF");
	m_text.setFont(m_font);
	m_text.setPosition(m_pos);
	m_text.setString(m_name);
	m_text.setFillColor(sf::Color(200, 0, 30));
	m_text.setCharacterSize(25);
	m_text.setOutlineColor(sf::Color::Black);
	m_text.setOutlineThickness(1);

	if (is_selected()) {
		m_text.setOutlineColor(sf::Color::Black);
		m_text.setOutlineThickness(6);
		m_text.setCharacterSize(30);
	}
	window.draw(m_text);
}

void Button::setName(std::string name)
{
	m_name = name;
}

void Button::setPos(sf::Vector2f pos)
{
	m_pos = pos;
}

sf::Vector2f Button::getPos() const
{
	return m_pos;
}

void Button::select()
{
	m_selected = true;
}

void Button::unselect()
{
	m_selected = false;
}

bool Button::is_selected() const
{
	return m_selected;
}


Button::Button(sf::Vector2f pos)
	:m_pos(pos)
{
}

Button::~Button()
{
}
