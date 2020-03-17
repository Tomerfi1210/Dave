#include "EndMenu.h"
#include "GameManager.h"


EndMenu::EndMenu()
{
}


EndMenu::~EndMenu()
{
}
void EndMenu::getInput(GameManager * manager)
{
	manager->getWindow().create(sf::VideoMode(END_WIDTH, END_HEIGHT), "DANGEROUS DAVE");
	sf::Event event;
	while (manager->getWindow().isOpen()) {
		while (manager->getWindow().pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				manager->getWindow().close();
				exit(0);
			}
			if (!pickButton(manager->getSound()))
				continue;
			else {
				switch (selectedBut()) {
				case RESTART_T:
					manager->startNewGame();
					return;
				case LEAVE_T:
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
EndMenu::EndMenu(bool win, int score)
{
	if (m_won)
		m_backGround.loadFromFile("Images\\win.jpeg");
	else
		m_backGround.loadFromFile("Images\\lose.jpg");
	m_backPic.setTexture(m_backGround);
	m_score = score;
	m_endTx.loadFromFile("Images\\bomberEnd.png");
	m_endSp.setTexture(m_endTx);
	m_endSp.setPosition(sf::Vector2f(END_WIDTH - 310, END_HEIGHT / 2));

	addButton("New Game");
	addButton("EXIT");
	m_button[0]->select();
	m_button[0]->setPos(sf::Vector2f((float)END_WIDTH / 2 - 150,
		(float)(MENU_HEIGHT / 5)*3.5));
	m_button[1]->setPos(sf::Vector2f((float)END_WIDTH / 2 - 50,
		(float)((MENU_HEIGHT / 5) * 4)));
}
//=============================================================================
void EndMenu::setButPos()
{
	m_button[0]->setPos(sf::Vector2f(END_WIDTH / 2 - 250,
		(END_HEIGHT / 5) * 3));
	m_button[1]->setPos(sf::Vector2f(END_WIDTH / 2 - 100,
		(END_HEIGHT / 5) * 4));
}
//=============================================================================
void EndMenu::draw(sf::RenderWindow & window)
{
	sf::Font font;

	font.loadFromFile("GOUDYSTO.TTF");

	m_scoreText.setFont(font);
	m_scoreText.setPosition(sf::Vector2f(END_WIDTH / 2 - 350, (END_HEIGHT / 20) * 4));
	std::string score = "your score is: " + std::to_string(m_score);
	m_scoreText.setString(score);
	m_scoreText.setFillColor(sf::Color::Magenta);
	m_scoreText.setCharacterSize(42);
	m_scoreText.setOutlineColor(sf::Color::Green);
	m_scoreText.setOutlineThickness(1);

	window.draw(m_backPic);
	window.draw(m_scoreText);
	window.draw(m_endSp);
	Menu::draw(window);
}
//=============================================================================
butType_t EndMenu::selectedBut() const
{
	return butType_t(m_selected + 20);
}