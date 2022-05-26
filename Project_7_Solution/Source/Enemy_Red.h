#ifndef __ENEMY_RED__
#define __ENEMY_RED__

#include "Enemy.h"
#include "Path.h"


class Enemy_Red : public Enemy
{
public:
	// Constructor (x y coordinates in the world)
	// Creates animation and movement data and the collider
	Enemy_Red(int x, int y);

	// The enemy is going to follow the different steps in the path
	// Position will be updated depending on the speed defined at each step
	void Update() override;

	void Attack();
private:
	// A set of steps that define the position in the screen
	// And an animation for each step
	Path path;

	bool alive = true;

	//delay between shots
	int delay1, bulletscounter;

	Collider* colliderEnemy = nullptr;
	// This enemy has one sprite and one frame
	// We are keeping it an animation for consistency with other enemies
	// The sprites used here are not the ones in the game
	Animation* currentanimationlegs;
	Animation Eup, Edown, Eleft, Eright, Eupleft, Eupright, Edownleft, Edownright;
	//Animation up, down, left, right, upleft, upright, downleft, downright;
	Animation Bup, Bdown, Bleft, Bright, BupL, BupR, BdownL, BdownR;
};


#endif // __ENEMY_RED__