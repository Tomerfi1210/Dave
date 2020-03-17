#include "PauseMenu.h"
#include "GameManager.h"


PauseMenu::PauseMenu()
{
	m_backGround.loadFromFile("Images\\background.jpg");
	m_backPic.setTexture(m_backGround);
	addButton("Continue");
	addButton("Sound ON");
	addButton("Exit");

	m_button[0]->select();

	m_button[0]->setPos(sf::Vector2f((float)MENU_WIDTH / 2 - 150,
		(float)(MENU_HEIGHT / 5)*3));
	m_button[1]->setPos(sf::Vector2f((float)MENU_WIDTH / 2 - 120,
		(float)((MENU_HEIGHT / 5) * 3.5)));
	m_button[2]->setPos(sf::Vector2f((float)MENU_WIDTH / 2 - 80,
		(float)((MENU_HEIGHT / 5) * 4)));

}


PauseMenu::~PauseMenu()
{
}
void PauseMenu::getInput(GameManager * manager)
{
	sf::Event event;
	manager->getWindow().create(sf::VideoMode(MENU_WIDTH, MENU_HEIGHT), "DANGEROUS DAVE");
	while (manager->getWindow().isOpen()) {
		while (manager->getWindow().pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				manager->getWindow().close();
				exit(0);
			}
			if (!this->pickButton(manager->getSound()))
				continue;
			else {
				switch (selectedBut()) {
				case CONTINUE_T:
					return;
					break;
				case SOUND_ON_T:
					manager->setSound();
					break;
				case EXIT_GAME_T:
					if (askWindow("\t\t are you sure ?")) {
						manager->getWindow().close();
						exit(0);
					}
					break;
				}
				break;
			}
		}
		manager->getWindow().clear();
		draw(manager->getWindow());
		manager->getWindow().display();
	}
}
//=============================================================================
butType_t PauseMenu::selectedBut() const
{
	return butType_t(m_selected + 10);
}
//=============================================================================
void PauseMenu::draw(sf::RenderWindow & window)
{
	window.draw(m_backPic);
	Menu::draw(window);
}
//=============================================================================
void PauseMenu::setButPos()
{
	for (size_t i = 0; i < m_button.size(); i++)
		m_button[i]->setPos(sf::Vector2f((float)MENU_WIDTH / 2 - 400,
		((float)MENU_HEIGHT / 6) * (i + 1)));
}

bool PauseMenu::askWindow(std::string str)
{
	sf::RenderWindow ask(sf::VideoMode(400, 200), str, sf::Style::Titlebar);

	sf::Event event;
	sf::Font font;
	font.loadFromFile("GOUDYSTO.TTF");
	sf::Text ansY("Yes", font, 40);
	sf::Text ansN("No", font, 40);
	ansY.setPosition(80, 70.f);
	ansN.setPosition(230, 70.f);
	ansY.setFillColor(sf::Color::Red);
	ansN.setFillColor(sf::Color::White);

	while (ask.isOpen()) {
		while (ask.waitEvent(event))
		{
			switch (event.type) {
			case sf::Event::KeyPressed:
				switch (event.key.code)
				{
				case sf::Keyboard::Left:
					ansY.setFillColor(sf::Color::Red);
					ansN.setFillColor(sf::Color::White);
					break;
				case sf::Keyboard::Right:
					ansN.setFillColor(sf::Color::Red);
					ansY.setFillColor(sf::Color::White);
					break;
				case sf::Keyboard::Return:
					if (ansY.getFillColor() == sf::Color::Red)
					{
						ask.close();
						return true;
					}
					else if (ansN.getFillColor() == sf::Color::Red)
					{
						ask.close();
						return false;
					}
					break;
				}
			}
			ask.draw(ansY);
			ask.draw(ansN);
			ask.display();
			ask.clear();
		}
	}
	return false;
}
