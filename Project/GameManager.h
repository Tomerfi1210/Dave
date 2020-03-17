#pragma once
#include "Board.h"
#include "PowerUp.h"
#include "Bullets.h"
#include "StartMenu.h"
#include "PauseMenu.h"
#include "EndMenu.h"
#include "Sound.h"
#include "GameInfo.h"
const int Width = 1074;
const int Height = 604;

class GameManager
{
public:
	GameManager();
	void run();
	sf::RenderWindow& getWindow();
	Sound& getSound();
	void setSound();
	void startNewGame();
	~GameManager() = default;
private:
	void states();
	Sound m_sound;
	GameInfo m_info;
	void dave_enemy_collision();
	std::unique_ptr<PauseMenu>m_menu;
	std::unique_ptr<Dave> m_dave;
	std::unique_ptr<Board>m_board;
	std::vector<std::unique_ptr<Enemy>>m_enemy;
	std::vector<std::unique_ptr<UnMoveAble>>m_staticBoard;//holds static objects.
	std::vector<std::unique_ptr<PowerUp>>m_powerUp;//holds gifts on board.
	std::unique_ptr<Bullets>m_DaveBullet;
	std::vector<std::unique_ptr<Bullets>>m_EnemyBullet;
	sf::RenderWindow m_window;
	void restartLvl();
	void collisions();
	void printBoard();
	void handleEvents(sf::RenderWindow & m_window, sf::Event & event);
	void updateJet();
	void dave_static_collision();
	void Davebullet_static_collision();
	void DaveBulletMove();
	void EnemyBulletMove();
	void moveAll();
	void setBullet();
	void setEnemyBullet();
	void dave_powerUp_collision();
	void EnemyBullet_static_collision();
	void dave_EnemyBullet_collision();
	void enemy_DaveBullet_collision();
	bool isGun = false;
	bool m_can_shoot = false;
	bool isEnemyDead = false;
	Direction_t  m_dir;
	sf::Clock m_JetTime;
	int m_JetTimeRemain = 0;
	int m_deltaTime = 0;
	bool alreadyFly = false;
	bool firstTime;
	std::vector<std::unique_ptr<UnMoveAble>> m_wonStatic;
	float m_winLimit;
	sf::Vector2f m_daveWinPos;

	void loadLvl(int);
	void updateWindow();
	void nextLvl();
	void printWin();
	void wonWalk();
	sf::Music m_music;
};