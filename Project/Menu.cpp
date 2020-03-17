#include "Menu.h"



Menu::Menu()
	:m_selected(0)
{
}


void Menu::draw(sf::RenderWindow & window)
{
	for (unsigned int i = 0; i < m_button.size(); i++)
		m_button[i]->draw(window);
}

bool Menu::pickButton(Sound & sound)
{
	SetSoundString(sound.mute());
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		sound.playMenu();
		SelectDown();
		return false;
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		sound.playMenu();
		SelectUp();
		return false;
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
	{
		sound.playClick();
		return true;
	}
	return false;
}

void Menu::SetSoundString(bool mute)
{
	if (m_button.size() == 3)
		if (mute)
			m_button[1]->setName("SOUND OFF");
		else
			m_button[1]->setName("SOUND ON");
}

void Menu::SelectUp()
{
	m_button[m_selected]->unselect();
	m_selected--;

	if (m_selected < 0)
		m_selected = m_button.size() - 1;

	m_button[m_selected]->select();
}

void Menu::SelectDown()
{
	m_button[m_selected]->unselect();
	m_selected++;

	if ((unsigned)m_selected >= m_button.size())
		m_selected = 0;

	m_button[m_selected]->select();
}


void Menu::addButton(std::string name)
{
	std::unique_ptr <Button> newBut = std::make_unique <Button>();
	newBut->setName(name);
	m_button.emplace_back(std::move(newBut));
}

Menu::~Menu()
{
}
