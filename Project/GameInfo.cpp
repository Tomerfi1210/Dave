#include "GameInfo.h"

GameInfo::GameInfo(int lvl, int score, int lives)
	:m_score(score), m_lvl(lvl), m_lives(lives), m_jetTime(120), isJet(false)
{
	m_font.loadFromFile("GOUDYSTO.TTF");
	m_lvlTxt.setFont(m_font);
	m_scoreTxt.setFont(m_font);
	m_livesTxt.setFont(m_font);
	m_jetTimeTxt.setFont(m_font);

	setUpTXT(m_scoreTxt, sf::Color::White);
	setUpTXT(m_lvlTxt, sf::Color::Yellow);
	setUpTXT(m_livesTxt, sf::Color(100, 155, 155));
	setUpTXT(m_jetTimeTxt, sf::Color::Cyan);
}

void GameInfo::resetNew()
{
	m_lives = 3;
	m_score = 0;
	m_prevScore = 0;
	m_lvl = 1;
	isJet = false;
	m_jetTime = 120;
}

void GameInfo::updateScore(int x)
{
	m_prevScore = m_score;
	m_score = x;
}

int GameInfo::getScore() const
{
	return m_score;
}

int GameInfo::getPrevScore() const
{
	return m_prevScore;
}

void GameInfo::updateLives(int x)
{
	m_lives = x;
}

int GameInfo::getLives() const
{
	return m_lives;
}

void GameInfo::updateLvl(int x)
{
	m_lvl = x;
}

int GameInfo::getLvl() const
{
	return m_lvl;
}

void GameInfo::setPos(int width, int height)
{
	m_lvlTxt.setCharacterSize(1140 / 30);
	m_livesTxt.setCharacterSize(1140 / 30);
	m_scoreTxt.setCharacterSize(1140 / 30);
	m_jetTimeTxt.setCharacterSize(1140 / 40);

	m_scoreTxt.setPosition(0, 10);
	m_lvlTxt.setPosition(width / 3.0f*1.1f, 10);
	m_livesTxt.setPosition(width / 3.0f*2.2f, 10);
	m_jetTimeTxt.setPosition(width / 4.0f*1.1f, height - 50.f);
}

void GameInfo::updateTxt()
{
	m_lvlTxt.setString("level: " + std::to_string(m_lvl));
	m_scoreTxt.setString("score: " + std::to_string(m_score));
	m_livesTxt.setString("life: " + std::to_string(m_lives));
}

void GameInfo::draw(sf::RenderWindow & window)
{
	updateTxt();
	window.draw(m_lvlTxt);
	window.draw(m_livesTxt);
	window.draw(m_scoreTxt);
	if(m_jetTime >= 0)
		window.draw(m_jetTimeTxt);
}

void GameInfo::resetTime(int x)
{
	x = x / 1000;
	int minute = x / (60);
	m_jetTime = x;
	std::string minutesLeft = std::to_string(minute),
		secondsLeft = std::to_string(x % (60));

	if (minute < 10)
		minutesLeft = "0" + minutesLeft;
	if (x % 60 < 10)
		secondsLeft = "0" + secondsLeft;
	m_jetTimeTxt.setString("Jet Time : " + minutesLeft + ":"
		+ secondsLeft);
	if (x < 11)
		m_jetTimeTxt.setFillColor(sf::Color::Red);
	else
		setUpTXT(m_jetTimeTxt, sf::Color::Cyan);
}

void GameInfo::setJet(bool x)
{
	isJet = x;
}



void GameInfo::setUpTXT(sf::Text & txt, sf::Color color)
{
	txt.setFillColor(color);
	txt.setOutlineThickness(3);
	txt.setOutlineColor(sf::Color::Black);
}
