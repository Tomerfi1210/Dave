#include "GameManager.h"
#include "CollisionHandler.h"
#include "Factory.h"
#include "PlayerMove.h"
#include <iostream>
#include <algorithm>

GameManager::GameManager() : m_board(std::make_unique<Board>()), m_DaveBullet(nullptr),
firstTime(true), m_menu(std::make_unique<PauseMenu>()), m_info(1, 0, 3)
{
	//m_board->readWonBoard(m_wonStatic);
	m_winLimit = m_board->getWinSize().width;
	m_daveWinPos = sf::Vector2f(STATIC_SIZE, 3 * STATIC_SIZE + 30);
	m_music.openFromFile("Sounds\\intro.wav");
	m_music.setLoop(true);
	m_music.setVolume(15);
	m_music.play();
}

void GameManager::run()
{
	startNewGame();
	sf::Event event{};
	while (m_window.isOpen())
	{
		m_window.clear();//clear the window.
		handleEvents(m_window, event);//close window.
		states();

		if (!m_dave->killed())
		{
			collisions();//checking collision with evey object in the game.
			moveAll();//moving all the moveable objects.
		}
		else if (m_dave->restart()) {
			m_sound.playLose();
			restartLvl();
		}
		if (m_dave->isWon()) {
			nextLvl();
			m_dave->setWon(false);
		}
		printBoard();//printing the object on screen.
		m_window.display();//display the window and sprites.
	}
}
sf::RenderWindow & GameManager::getWindow()
{
	return m_window;
}
Sound & GameManager::getSound()
{
	return m_sound;
}
void GameManager::setSound()
{
	m_sound.setSound();
	if (m_sound.mute())
		m_music.pause();
	else
		m_music.play();
}
//------------------------------------------------------------------
void GameManager::states()
{
	if(m_dave->getStrategy()->isFly())//Flying state.
	{
		m_JetTimeRemain += (int)m_JetTime.getElapsedTime().asSeconds() - m_deltaTime;
		if (m_JetTimeRemain > 100000)
		{
			m_dave->setJet(false);
			m_dave->getStrategy()->setCanFly(false);
			alreadyFly = false;
		}
		//used jet already and i can use jet but not flying right now.
		if (alreadyFly && !m_dave->getStrategy()->isFly())
			m_deltaTime += m_JetTime.getElapsedTime().asSeconds();
	}
	m_info.resetTime(100000 - m_JetTimeRemain);
	if (m_dave->getSprite().getPosition().x > m_board->getWindowSize().width) {
		loadLvl(m_info.getLvl() + 1);
		m_dave->setStrategy(std::make_unique<PlayerMove>(*m_dave));
	}
}
//-------------------------------------------------------------------
void GameManager::printBoard()
{
	if (m_DaveBullet) m_DaveBullet->draw(m_window);
	for (const auto& bullet : m_EnemyBullet) if (bullet) bullet->draw(m_window);
	std::for_each(m_staticBoard.begin(), m_staticBoard.end(), [this](const auto& stat) {stat->draw(m_window); });
	m_dave->draw(m_window);
	std::for_each(m_enemy.begin(), m_enemy.end(), [this](const auto& enemy) {enemy->draw(m_window); });
	std::for_each(m_powerUp.begin(), m_powerUp.end(), [this](const auto& gift) {gift->draw(m_window);});
	m_info.draw(m_window);
}
//-----------------------------------------------------------------------
void GameManager::handleEvents(sf::RenderWindow &m_window, sf::Event &event)
{
	if (m_window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			m_window.close();
			break;
		case sf::Event::LostFocus:
			m_menu->getInput(this);
			m_window.create(m_board->getWindowSize(), 32u, sf::Style::Close);
			break;
		case sf::Event::KeyPressed:
			switch (event.key.code)
			{
			case sf::Keyboard::Escape:
				m_menu->getInput(this);
				m_window.create(m_board->getWindowSize(), 32u, sf::Style::Close);
				break;
			case sf::Keyboard::LAlt:
				if (!m_dave->HaveGun())
					break;
				if(!m_DaveBullet)
					setBullet();
				break;
			case sf::Keyboard::LControl://to fly with jet(if possiable)
				if(!m_dave->HaveJet())//if not collide with jet, wont be able to fly.
					break;
				updateJet();
				break;
			}
			break;
		}
	}
	m_dave->directionSet();//first we select the direction we want.
	setEnemyBullet();
}
//-----------------------------------------------------------------------
void GameManager::updateJet()
{
	m_JetTime.restart();
	if (m_dave->getStrategy()->isFly()) {//to cancel fly if already flying.
		m_dave->getStrategy()->setCanFly(false);
	}
	else {//make him fly with jet.
		m_dave->getStrategy()->setCanFly(true);
		alreadyFly = true;
	}	
}
//-----------------------------------------------------------------------
void GameManager::dave_static_collision()
{
	int collisionTimes = 0;
	m_dave->setCollision();
	if (m_dave->getStrategy()->getStep().y == 0 && !m_dave->getStrategy()->isFly())
		m_dave->getStrategy()->getStep().y = (float)0.7;
	for (const auto& stat : m_staticBoard)
	{
		if (isCollision(stat->getRect(), m_dave->getRect())) {
			processCollision(*m_dave, *stat);
			collisionTimes++;
		}
		if (collisionTimes >= 3)
			break;
	}
}

void GameManager::Davebullet_static_collision()
{
	for (const auto& stat : m_staticBoard)
	{
		if (isCollision(stat->getRect(), m_DaveBullet->getRect())) {
			processCollision(*m_DaveBullet, *stat);
			m_DaveBullet.reset();
			break;
		}
	}
}
void GameManager::DaveBulletMove()
{
	if (m_DaveBullet) 
	{
		if (m_dave->killed()) {
			m_DaveBullet.reset();
			return;
		}
		if (m_dir == Right) {
			m_DaveBullet->getSprite().setScale({ -1, 1 });
			m_DaveBullet->move({ 1,0 });
		}
		else {
			m_DaveBullet->getSprite().setScale({ 1, 1 });
			m_DaveBullet->move({ -1, 0 });
		}
	}
}

void GameManager::EnemyBulletMove()
{
	for (size_t i = 0 ; i < m_enemy.size() ; i++)
	{
		if (m_enemy[i]->killed() && m_EnemyBullet[i]) {
			m_EnemyBullet[i].reset();
			continue;
		}
		if (m_EnemyBullet[i])
		{
			if (m_dave->getPosition().x > m_enemy[i]->getPosition().x) {
				m_EnemyBullet[i]->getSprite().setScale({ -1, 1 });
				m_EnemyBullet[i]->move({ 1, 0 });
			}
			else {
				m_EnemyBullet[i]->getSprite().setScale({ 1, 1 });
				m_EnemyBullet[i]->move({ -1, 0 });
			}
		}
	}
}

void GameManager::moveAll()
{
	m_dave->move();//second we move the player

	std::for_each(m_enemy.begin(), m_enemy.end(), [this](const auto& enemy) 
	{
		if(!enemy || !enemy->killed())
			enemy->move(m_dave->getSprite().getPosition());
	});	
	DaveBulletMove();
	EnemyBulletMove();
}

void GameManager::setBullet()
{
	sf::Vector2f pos = m_dave->getSprite().getPosition();
	pos = { pos.y / 60, pos.x / 60 };
	m_dir = m_dave->getStrategy()->getDir();
	m_DaveBullet = Factory<Bullets>::create(Textures::Default_Bullet_c, pos);
}

void GameManager::setEnemyBullet()
{
	sf::Vector2f pos;
	for (size_t i = 0 ; i < m_enemy.size() ; i++)
	{
		if (m_enemy[i]->killed() && m_EnemyBullet[i]) {
			m_EnemyBullet[i].reset();
			continue;
		}
		pos = m_enemy[i]->getPosition();
		pos = { pos.y / 60, pos.x / 60 };	
		if (m_EnemyBullet[i] || !m_enemy[i]->TimeLimit())
			continue;
		m_EnemyBullet[i] = Factory<Bullets>::create(Textures::Enemy_Bullet_c, pos);
		m_enemy[i]->resetClock();
	}
}

void GameManager::dave_powerUp_collision()
{
	for (size_t i = 0; i < m_powerUp.size(); i++)
	{
		if (isCollision(m_powerUp[i]->getRect(), m_dave->getRect())) {
			processCollision(*m_dave, *m_powerUp[i]);
			m_powerUp.erase(m_powerUp.begin() + i);
		}
	}
}

void GameManager::EnemyBullet_static_collision()
{
	for (size_t i = 0; i < m_EnemyBullet.size(); i++)
	{
		for(const auto& stat : m_staticBoard)
		{
			if (m_EnemyBullet[i] && isCollision(stat->getRect(), m_EnemyBullet[i]->getRect()))
			{
				processCollision(*m_EnemyBullet[i], *stat);
				m_EnemyBullet[i].reset();
				break;
			}
		}
		
	}
}

void GameManager::dave_EnemyBullet_collision()
{
	for (auto& bullet : m_EnemyBullet)
	{
		if (bullet && isCollision(m_dave->getRect(), bullet->getRect())) {
			processCollision(*m_dave, *bullet);
			bullet.reset();
			return;
		}
	}
}

void GameManager::enemy_DaveBullet_collision()
{
	static int dead_index;
	for (size_t i = 0 ; i < m_enemy.size() ; i++)
	{
		if (m_DaveBullet && isCollision(m_enemy[i]->getRect(), m_DaveBullet->getRect()))
		{
			processCollision(*m_enemy[i], *m_DaveBullet);
			dead_index = i;
			m_DaveBullet.reset();
			return;
		}
		if (m_enemy[i]->killed() && m_enemy[i]->TimeToDie())
			m_enemy.erase(m_enemy.begin() + dead_index);
	}
}

void GameManager::startNewGame()
{
	if (firstTime)
	{
		std::unique_ptr<StartMenu> m_menu = std::make_unique<StartMenu>();
		m_menu->getInput(this);
		firstTime = false;
	}
	m_info.resetNew();
	loadLvl(m_info.getLvl());
}

void GameManager::loadLvl(int lvl)
{
	m_staticBoard.clear();
	if (m_dave) {
		m_dave->setGun(false);
		m_dave->setJet(false);
	}
	m_enemy.clear();
	m_EnemyBullet.clear();
	//m_dave.reset(nullptr);
	m_powerUp.clear();
	m_DaveBullet.reset(nullptr);
	std::string file_name = "Levels\\lvl" + std::to_string(lvl) + ".txt";
	if (!m_board->readLvl(file_name, m_dave, m_staticBoard, m_enemy, m_powerUp)) {
		m_sound.playOver();
		std::unique_ptr<EndMenu> m_menu = std::make_unique<EndMenu>(true, m_info.getScore());
		m_menu->getInput(this);
	}
	updateWindow();
}

void GameManager::updateWindow()
{
	m_EnemyBullet.resize(m_enemy.size());//enemy bullet.
	m_dave->setInfo(&m_info);
	m_window.create(m_board->getWindowSize(), 32u, sf::Style::Close);
	m_info.setPos(m_board->getWindowSize().width, m_board->getWindowSize().height);
	printBoard();
	m_window.display();
}

void GameManager::nextLvl()
{
	m_sound.playWin();
	sf::sleep(sf::seconds(1));
	//wonWalk();
	m_info.updateLvl(m_info.getLvl()+1);
	loadLvl(m_info.getLvl());
}

void GameManager::printWin()
{
	for (size_t i = 0; i < m_wonStatic.size(); i++)
		m_wonStatic[i]->draw(m_window);
	m_dave->draw(m_window);
}

void GameManager::wonWalk()
{
		m_window.create(m_board->getWinSize(), "DANGEROUS DAVE");
		m_dave->setStrategy(std::make_unique<PlayerMove>(*m_dave));
}

void GameManager::restartLvl()
{
	if (m_dave->isDead()) {
		m_sound.playOver();
		std::unique_ptr<EndMenu> m_menu = std::make_unique<EndMenu>(false, m_info.getScore());
		m_menu->getInput(this);
	}

	m_dave->resetPos();
	std::for_each(m_enemy.begin(), m_enemy.end(), [this](const auto& enemy) {enemy->resetPos();});
	m_dave->resetKill();
	m_dave->getSprite().setOrigin(sf::Vector2f{ DYNAMIC_SIZE / 2, DYNAMIC_SIZE / 2 });
	m_dave->getSprite().move(DYNAMIC_SIZE / 2, DYNAMIC_SIZE / 2);
	m_info.updateLives(m_info.getLives() - 1);
}

void GameManager::collisions()
{
	dave_static_collision(); //checking collision dave with static objects and handlig jump and down.

	if(m_DaveBullet) Davebullet_static_collision(); //checking collision bullet and static object.

	EnemyBullet_static_collision();//checking collision of enemy bullet with static object.

	dave_powerUp_collision(); //checking collision dave with power ups.

	dave_EnemyBullet_collision();//checkink collision dave and enemy bullet.

	enemy_DaveBullet_collision();//checking collision enemy and dave bullet.
	dave_enemy_collision();
}
void GameManager::dave_enemy_collision()
{
	static int dead_index = -1;
	for (size_t i = 0; i < m_enemy.size(); i++)
	{
		if (m_enemy[i] && isCollision(m_enemy[i]->getRect(), m_dave->getRect()))
		{
			processCollision(*m_dave, *m_enemy[i]);
			dead_index = i;
			return;
		}
		if (m_enemy[i]->killed() && m_enemy[i]->TimeToDie())
			m_enemy.erase(m_enemy.begin() + dead_index);
	}
}