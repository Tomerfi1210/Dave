#pragma once
#include "SFML/Graphics.hpp"
class GameInfo
{
public:
	//static GameInfo& get_instance(int lvl, int score, int lives);
	GameInfo() = default;
	GameInfo(int lvl, int score, int lives);
	~GameInfo() = default;

	void resetNew();
	//set score to be x
	void updateScore(int x);
	//return the current score
	int getScore() const;
	int getPrevScore()const;

	//set lives to be x
	void updateLives(int x);
	//returns the lives
	int getLives() const;

	//set level to be x
	void updateLvl(int x);
	//return the current level number
	int getLvl()const;

	//this func sets the position of the information
	void setPos(int width, int height);
	//this func updates the text according to the process
	void updateTxt();
	//this func draws the info to the windoq
	void draw(sf::RenderWindow &window);

	void resetTime(int x);
	void setJet(bool);


private:
	int m_lvl,
		m_score,
		m_lives,
		m_prevScore,
		m_jetTime;


	sf::Font m_font;

	sf::Text m_lvlTxt,
			m_scoreTxt,
			m_livesTxt,
			m_jetTimeTxt;

	//this func sets the text to each one of the information
	void setUpTXT(sf::Text& txt, sf::Color color);
	bool isJet;

};

