#include "StartMenu.h"
#include "GameManager.h"


StartMenu::StartMenu()
{
	m_backGround.loadFromFile("Images\\background.jpg");
	m_backPic.setTexture(m_backGround);

	addButton("START NEW GAME");
	addButton("EXIT");

	m_button[0]->select();

	m_button[0]->setPos(sf::Vector2f((float)MENU_WIDTH / 2 - 250,
		(float)(MENU_HEIGHT / 5)*3.5));
	m_button[1]->setPos(sf::Vector2f((float)MENU_WIDTH / 2 - 100,
		(float)((MENU_HEIGHT / 5)*4 )));
}
void StartMenu::getInput(GameManager *manager)
{
	manager->getWindow().create(sf::VideoMode(MENU_WIDTH, MENU_HEIGHT), "DANGEROUS DAVE");
	sf::Event event;
	while (manager->getWindow().isOpen()) {
		while (manager->getWindow().pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				manager->getWindow().close();
				exit(0);
			}
			if (!(this)->pickButton(manager->getSound()))
				continue;
			else {
				switch (this->selectedBut()) {
				case START_T:
					return;
				case EXIT_T:
					manager->getWindow().close();
					exit(0);
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
void StartMenu::setButPos()
{
	for (unsigned int i = 0; i < m_button.size(); i++)
		m_button[i]->setPos(sf::Vector2f((float)MENU_WIDTH / 2,
		(float)(MENU_HEIGHT / 5) * (i + 1)));
}
//=============================================================================
void StartMenu::draw(sf::RenderWindow & window)
{
	window.draw(m_backPic);
	Menu::draw(window);
}
//=============================================================================
butType_t StartMenu::selectedBut() const
{
	return butType_t(m_selected);
}
