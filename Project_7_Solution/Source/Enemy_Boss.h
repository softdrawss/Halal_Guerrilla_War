#ifndef __ENEMY_BOSS_H__
#define __ENEMY_BOSS_H__

#include "Enemy.h"
#include "Path.h"

class Enemy_Boss : public Enemy
{
public:
	// Constructor (x y coordinates in the world)
	// Creates animation and movement data and the collider
	Enemy_Boss(int x, int y);

	// The enemy is going to follow the different steps in the path
	// Position will be updated depending on the speed defined at each step
	void Update() override;

	void movedownupshoot();

	void OnCollision(Collider* collider)override;

	void firemissiles();

private:
	// A set of steps that define the position in the screen
	// And an animation for each step
	Path pathup, pathdown, pathleft, pathright;

	// This enemy has one sprite and one frame
	// We are keeping it an animation for consistency with other enemies
	Animation fly, deathanim;
	int notmovingcounter;
	int hitpoints;
};

#endif // __ENEMY_BOSS_H__ 