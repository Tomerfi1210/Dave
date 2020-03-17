#include "CollisionHandler.h"
#include <iostream>
#include <map>
#include <string>
#include <typeinfo>
#include <typeindex>
#include "Dave.h"
#include "Enemy.h"
#include "Gun.h"
#include "DefaultBullet.h"
#include "EnemyBullet.h"
#include "Wall.h"
#include "JetPack.h"
#include "Fire.h"
#include "Water.h"
#include "Door.h"
#include "Electricity.h"
#include "CircleEnemy.h"
#include "HorizontalEnemy.h"
#include "StraightMove.h"
#include "Diamond.h"
#include "Rock.h"

namespace { // anonymous namespace — the standard way to make function "static"

// primary collision-processing functions
	void DaveWall(GameObject& Player,
		GameObject& wall)
	{
		Dave& dave = dynamic_cast<Dave&>(Player);

		float daveX = dave.getSprite().getGlobalBounds().left;
		float daveY = dave.getSprite().getGlobalBounds().top;
		float wallX = wall.getSprite().getGlobalBounds().left;
		float wallY = wall.getSprite().getGlobalBounds().top;

		float XDistance = abs(wallX - daveX);
		float YDistance = abs(wallY - daveY);
		
		float stepX = dave.getStrategy()->getStep().x;
		float stepY = dave.getStrategy()->getStep().y;
		
		//left and right wall.
		if (XDistance < 50 && YDistance < 49
			&& ((stepX < 0 && wallX < daveX)
				|| (stepX > 0 && wallX > daveX))
			&& !dave.collisionX)
		{
			dave.getStrategy()->getStep().x = 0;
			dave.collisionX = true;
			//dave.m_move->setJump(false);
		}
		
		//under him wall.
		if (YDistance < 50 && XDistance < 49
			&& ((stepY < 0 && wallY < daveY)
				|| (stepY > 0 && wallY > daveY))
			&& !dave.collisionY)
		{
			dave.getStrategy()->getStep().y = 0;
			dave.getStrategy()->setJump(true);
			dave.collisionY = true;
		}
		
	}
	//End Dave Wall.
	//-------------------------------------
	void EnemyWall(GameObject& enemyObject,
		GameObject& staticWall)
	{
		Enemy& enemy = dynamic_cast<Enemy&>(enemyObject);
		//Wall& wall = dynamic_cast<Wall&>(staticWall);

	}
	//End Enemy Wall.
	//-------------------------------------
	void PlayerGun(GameObject& player,
		GameObject& gunObject)
	{
		Dave& dave = dynamic_cast<Dave&>(player);

		dave.setGun(true);
	}
	//End Player Gun.
	//---------------------------------------
	void BulletStatic(GameObject& bullets,
		GameObject& staticWall)
	{
		Bullets& bullet = dynamic_cast<Bullets&>(bullets);

	}
	//End Bullet Wall.
	//-----------------------------------------
	void PlayerJetPack(GameObject& player,
		GameObject& jet)
	{
		Dave& dave = dynamic_cast<Dave&>(player);
		JetPack& wall = dynamic_cast<JetPack&>(jet);
		
		dave.setJet(true);
	}
	//End Player JetPack.
	//----------------------------------------------
	void PlayerKill(GameObject& player,
		GameObject& fireObject)
	{
		Dave& dave = dynamic_cast<Dave&>(player);

		dave.kill();
	}
	//------------------------------------------------
	void PlayerDoor(GameObject& player,
		GameObject& doorObkect)
	{
		Dave& dave = dynamic_cast<Dave&>(player);

		dave.setWon(true);
		dave.setWinPos();
		dave.setStrategy(std::make_unique<StraightMove>(dave));
		dave.getSprite().setScale({ 1,1 });
		dave.getStrategy()->setSpeed(10);
		//dave.setStraight(true);
	}
	//------------------------------------------------
	void EnemyVsBullet(GameObject& enem,
		GameObject& bull)
	{
		Enemy& enemy = dynamic_cast<Enemy&>(enem);

		enemy.setKill(true);
		enemy.resetClockDie();
	}
//----------------------------------------------------------------------------------------------\\
	// secondary collision-processing functions that just
	// implement symmetry: swap the parameters and call a
	// primary function
	void WallDave(GameObject& player,
		GameObject& wall)
	{
		DaveWall(player, wall);
	}
	//------------------------
	void WallEnemy(GameObject& Enemy,
		GameObject& wall)
	{
		EnemyWall(Enemy, wall);
	}
	//------------------------
	void GunPlayer(GameObject& player,
		GameObject& gun)
	{
		PlayerGun(player, gun);
	}
	//---------------------
	void StaticBullet(GameObject& bullet,
		GameObject& wall)
	{
		BulletStatic(bullet, wall);
	}
	//---------------
	void JetPackPlayer(GameObject& player,
		GameObject& jet)
	{
		PlayerJetPack(player, jet);
	}
	//---------------
	void KillPlayer(GameObject& player,
		GameObject& fire)
	{
		PlayerKill(player, fire);
	}
	//-----------------------------
	void DoorPlayer(GameObject& player,
		GameObject& door)
	{
		PlayerDoor(player, door);
	}
	void BulletVsEnemy(GameObject& enemy,
		GameObject& bullet)
	{
		EnemyVsBullet(enemy, bullet);
	}
	void PlayerDiamond(GameObject& player, GameObject&dia)
	{
		Dave& dave = dynamic_cast<Dave&>(player);
		dave.addScore();
	}
	void DiamondPlayer(GameObject& dia, GameObject&dave)
	{
		PlayerDiamond(dave, dia);
	}
	//----------------------------------
	void DaveCircle(GameObject& player,
		GameObject& enem)
	{
		Dave& dave = dynamic_cast<Dave&>(player);
		CircleEnemy& enemy = dynamic_cast<CircleEnemy&>(enem);

		dave.kill();
		enemy.setKill(true);
		enemy.resetClockDie();
	}

	void DaveHorizontal(GameObject& player,
		GameObject& enem)
	{
		Dave&dave= dynamic_cast<Dave&>(player);
		HorizontalEnemy& enemy = dynamic_cast<HorizontalEnemy&>(enem);

		dave.kill();
		enemy.setKill(true);
		enemy.resetClockDie();
	}
	void CircleDave(GameObject& dave,
		GameObject& enemy)
	{
		DaveCircle(dave, enemy);
	}
	void HorizontalDave(GameObject& dave,
		GameObject& enemy)
	{
		DaveHorizontal(dave, enemy);
	}

//-------------------------------------------------------------------------
	using HitFunctionPtr = void(*)(GameObject&, GameObject&);
	using Key = std::pair<std::type_index, std::type_index>;
	using HitMap = std::map<Key, HitFunctionPtr>;

	HitMap initializeCollisionMap()
	{
		HitMap phm;
		phm[Key(typeid(Dave), typeid(Wall))] = &DaveWall;
		phm[Key(typeid(Wall), typeid(Dave))] = &WallDave;
		phm[Key(typeid(Dave), typeid(Rock))] = &DaveWall;
		phm[Key(typeid(Rock), typeid(Dave))] = &WallDave;

		phm[Key(typeid(Enemy), typeid(Wall))] = &EnemyWall;
		phm[Key(typeid(Wall), typeid(Enemy))] = &WallEnemy;
		phm[Key(typeid(Enemy), typeid(Rock))] = &EnemyWall;
		phm[Key(typeid(Rock), typeid(Enemy))] = &WallEnemy;

		phm[Key(typeid(Dave), typeid(Gun))] = &PlayerGun;
		phm[Key(typeid(Gun), typeid(Dave))] = &GunPlayer;
		phm[Key(typeid(DefaultBullet), typeid(Wall))] = &BulletStatic;
		phm[Key(typeid(Wall), typeid(DefaultBullet))] = &StaticBullet;
		phm[Key(typeid(DefaultBullet), typeid(Rock))] = &BulletStatic;
		phm[Key(typeid(Rock), typeid(DefaultBullet))] = &StaticBullet;

		phm[Key(typeid(Dave), typeid(JetPack))] = &PlayerJetPack;
		phm[Key(typeid(JetPack), typeid(Dave))] = &JetPackPlayer;
		phm[Key(typeid(Dave), typeid(Fire))] = &PlayerKill;
		phm[Key(typeid(Fire), typeid(Dave))] = &KillPlayer;
		phm[Key(typeid(Dave), typeid(Water))] = &PlayerKill;
		phm[Key(typeid(Water), typeid(Dave))] = &KillPlayer;
		phm[Key(typeid(Dave), typeid(Electricity))] = &PlayerKill;
		phm[Key(typeid(Electricity), typeid(Dave))] = &KillPlayer;
		phm[Key(typeid(Dave), typeid(DefaultBullet))] = &PlayerKill;
		phm[Key(typeid(DefaultBullet), typeid(Dave))] = &KillPlayer;
		phm[Key(typeid(Dave), typeid(CircleEnemy))] = &KillPlayer;
		phm[Key(typeid(CircleEnemy), typeid(Dave))] = &KillPlayer;
		phm[Key(typeid(Dave), typeid(HorizontalEnemy))] = &KillPlayer;
		phm[Key(typeid(HorizontalEnemy), typeid(Dave))] = &KillPlayer;

		phm[Key(typeid(Dave), typeid(Door))] = &PlayerDoor;
		phm[Key(typeid(Door), typeid(Dave))] = &DoorPlayer;

		phm[Key(typeid(DefaultBullet), typeid(Fire))] = &BulletStatic;
		phm[Key(typeid(Fire), typeid(DefaultBullet))] = &StaticBullet;

		phm[Key(typeid(EnemyBullet), typeid(Fire))] = &StaticBullet;
		phm[Key(typeid(Fire), typeid(EnemyBullet))] = &StaticBullet;
		phm[Key(typeid(EnemyBullet), typeid(Wall))] = &StaticBullet;
		phm[Key(typeid(Wall), typeid(EnemyBullet))] = &StaticBullet;
		phm[Key(typeid(EnemyBullet), typeid(Rock))] = &StaticBullet;
		phm[Key(typeid(Rock), typeid(EnemyBullet))] = &StaticBullet;

		phm[Key(typeid(Dave), typeid(EnemyBullet))] = &PlayerKill;
		phm[Key(typeid(EnemyBullet), typeid(Dave))] = &KillPlayer;

		phm[Key(typeid(DefaultBullet), typeid(CircleEnemy))] = &BulletVsEnemy;
		phm[Key(typeid(CircleEnemy), typeid(DefaultBullet))] = &EnemyVsBullet;
		phm[Key(typeid(HorizontalEnemy), typeid(DefaultBullet))] = &EnemyVsBullet;
		phm[Key(typeid(DefaultBullet), typeid(HorizontalEnemy))] = &EnemyVsBullet;

		phm[Key(typeid(Dave), typeid(Diamond))] = &PlayerDiamond;
		phm[Key(typeid(Diamond), typeid(Dave))] = &DiamondPlayer;

		phm[Key(typeid(Dave), typeid(CircleEnemy))] = &DaveCircle;
		phm[Key(typeid(CircleEnemy), typeid(Dave))] = &CircleDave;

		phm[Key(typeid(Dave), typeid(HorizontalEnemy))] = &DaveHorizontal;
		phm[Key(typeid(HorizontalEnemy), typeid(Dave))] = &HorizontalDave;
		
		return phm;
	}

	HitFunctionPtr lookup(const std::type_index& class1, const std::type_index& class2)
	{
		static HitMap collisionMap = initializeCollisionMap();
		auto mapEntry = collisionMap.find(std::make_pair(class1, class2));
		if (mapEntry == collisionMap.end())
		{
			return nullptr;
		}
		return mapEntry->second;
	}

} // end namespace

bool isCollision(const sf::FloatRect &obj1, const sf::FloatRect &obj2)
{
	sf::FloatRect temp = { obj1.left - 1, obj1.top - 2, obj1.width - 2, obj1.height - 2 };
	//in order to check the next move
	sf::FloatRect newRec = { obj2.left + 1.f,
							obj2.top + 2.f,
							obj2.width, obj2.height - 2 };
	return (temp.intersects(newRec));
}

void processCollision(GameObject& object1, GameObject& object2)
{
	auto phf = lookup(typeid(object1), typeid(object2));
	if (!phf)
	{
		throw UnknownCollision(object1, object2);
	}
	phf(object1, object2);
}
