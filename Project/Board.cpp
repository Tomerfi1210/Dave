#include "Board.h"
#include "Bullets.h"
//#include "PowerUp.h"
#include "Factory.h"


bool Board::readLvl(std::string file_name, std::unique_ptr<Dave>& dave, std::vector<std::unique_ptr<UnMoveAble>>& staticBoard, 
	std::vector<std::unique_ptr<Enemy>>& enemy, std::vector<std::unique_ptr<PowerUp>>& gift)
{

	ifstream m_level;
	m_level.open(file_name);
	if (!m_level.is_open())
		return false;

	m_level >> m_row;
	m_level >> m_col;

	for (int i = 0; i < m_row; i++)
	{
		for (int j = 0; j < m_col; j++)
		{
			char c = m_level.get();

			if (c == '\n') {
				j--;
				continue;
			}

			sf::Vector2f pos = { (float)(i + 1), (float)j };
			//trying to get pointer of unmoveable object
			auto ptr = Factory<UnMoveAble>::create(c, pos);
			if (ptr != nullptr) { //if it is not nullptr it is unmoveable
				staticBoard.push_back(std::move(ptr));
				continue;
			}

			auto ptr2 = Factory<Enemy>::create(c, pos);
			if (ptr2 != nullptr) {
				enemy.push_back(std::move(ptr2));
				continue;
			}
			
			auto ptr3 = Factory<PowerUp>::create(c, pos);
			if (ptr3 != nullptr) {
				gift.push_back(std::move(ptr3));
				continue;
			}
			else if (c == Textures::Dave_c)
			{
				if (dave == nullptr)
					dave = std::make_unique<Dave>(pos);
				else {
					dave->getSprite().setPosition({ pos.y * STATIC_SIZE, pos.x * STATIC_SIZE });
					dave->getSprite().setOrigin(sf::Vector2f{ DYNAMIC_SIZE / 2, DYNAMIC_SIZE / 2 });
					dave->getSprite().move(DYNAMIC_SIZE / 2, DYNAMIC_SIZE / 2);

				}
			}
			//else if (c == Robot_c)
			//{
			//	if (robot == nullptr)
			//		robot = std::make_unique<Robot>(pos);
			//	else
			//		robot->setPosition(pos);
			//}
			/*if (c == Textures::Dave_c) {
				dave = std::make_unique<Dave>(pos);
			}*/
		}
	}
	m_level.close();
	return true;
}

void Board::readWonBoard(std::vector<std::unique_ptr<UnMoveAble>>& wonBoard)
{
	ifstream m_won;
	int rows, cols;
	m_won.open("Levels\\wonLvl.txt");
	
	m_won >> rows;
	m_won >> cols;

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			char c = m_won.get();

			if (c == '\n') {
				j--;
				continue;
			}

			sf::Vector2f pos = { (float)(i), (float)j };
			//trying to get pointer of unmoveable object
			auto ptr = Factory<UnMoveAble>::create(c, pos);
			if (ptr != nullptr) { //if it is not nullptr it is unmoveable
				wonBoard.push_back(std::move(ptr));
				continue;
			}
		}
	}
	m_won.close();
}

sf::VideoMode Board::getWindowSize()
{
	return sf::VideoMode(m_col * STATIC_SIZE,
		(2+m_row) * STATIC_SIZE);
}

sf::VideoMode Board::getWinSize()
{
	return sf::VideoMode(15 * STATIC_SIZE, 7 * STATIC_SIZE);
}
