#pragma once
#include "ChangeMove.h"
#include <iostream>
#include "GameInfo.h"

class Dave : public ChangeMove
{
public:
	Dave() = default;
	Dave(sf::Vector2f& startpos);
	~Dave() = default;
	int getLife() const { return m_life; }
	void directionSet();
	virtual void move(sf::Vector2f d = { 0.f, 0.f }) override;
	sf::FloatRect getRect() override;
	void setCollision() { collisionX = collisionY = false; }
	bool getCollision() { return collisionX && collisionY; }
	bool collisionX;
	bool collisionY;
	virtual void setStrategy(std::unique_ptr<MoveStrategy>) override;
	bool HaveGun() const { return m_isGun; }
	bool HaveJet() const { return m_isJet; }
	void setGun(const bool& gun) { m_isGun = gun; }
	void setJet(const bool& jet) { m_isJet = jet; }
	void draw(sf::RenderWindow& window) override;
	void kill() { m_life--; isKilled = true; m_clock.restart(); m_move->setCanFly(false); }
	void resetKill() { isKilled = false; }
	bool isDead() const { if (m_life <= 0)return true; else return false; }//GameOver.
	bool restart() const { return m_clock.getElapsedTime().asSeconds() >= limitDead; }
	void setWon(const bool& won) { m_won = won; }
	bool isWon() const { return m_won; }
	void setStraight(const bool & s) { m_straight = s; }
	void setWinPos() { m_sprite.setPosition(m_daveWinPos); }
	void setInfo(GameInfo * info);
	void addScore();
private:
	bool m_collision;
	int m_life;
	GameInfo *m_info;
	bool m_isGun = false;
	bool m_isJet = false;
	bool m_won = false;
	sf::Sprite m_JetSprite;
	sf::Texture *m_Jet = nullptr;
	float speed = 0.5f;
	bool m_straight = false;
	sf::Vector2f m_daveWinPos = sf::Vector2f(STATIC_SIZE, 3 * STATIC_SIZE + 30);
};