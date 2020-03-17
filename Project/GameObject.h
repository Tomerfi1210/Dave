#pragma once
#include "MoveStrategy.h"
#include "Animation.h"
const int DYNAMIC_SIZE = 50;
const int STATIC_SIZE = 60;

class Bullets;

class GameObject
{
public:
	GameObject(sf::Vector2f& pos);
	GameObject();
	virtual void draw(sf::RenderWindow & window);
	void resetPos();
	sf::Vector2f getPosition() const { return m_sprite.getPosition(); }
	void setPosition(const sf::Vector2f &pos) { m_startLocation = pos; }
	sf::Sprite& getSprite()  { return m_sprite; }
	virtual void move(sf::Vector2f = { 0.f, 0.f }) {};
	virtual ~GameObject() = 0;
	virtual sf::FloatRect getRect() { return m_sprite.getGlobalBounds(); }
protected:
	sf::Vector2f m_startLocation;
	sf::Sprite m_sprite;
	sf::Texture *m_texture = nullptr;
	Animation m_animation;
};

