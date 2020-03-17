#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include "Dave.h"
#include "Enemy.h"
#include "UnMoveAble.h"
#include "Bullets.h"
#include "PowerUp.h"

using std::ifstream;
class Board
{
public:
	Board() = default;
	~Board() = default;
	bool readLvl(std::string file_name, std::unique_ptr<Dave>& dave, std::vector<std::unique_ptr<UnMoveAble>>& staticBoard,
		std::vector<std::unique_ptr<Enemy>>& enemy, std::vector<std::unique_ptr<PowerUp>>&);
	void readWonBoard(std::vector<std::unique_ptr<UnMoveAble>>&);
	sf::VideoMode getWindowSize();
	sf::VideoMode getWinSize();
private:
	int m_row, m_col;
};

