#ifndef __ENEMY_RED__
#define __ENEMY_RED__

#include "Enemy.h"
#include "Path.h"


class Enemy_Red : public Enemy
{
public:
	// Constructor (x y coordinates in the world)
	// Creates animation and movement data and the collider
	Enemy_Red(int x, int y, int movingbehaviour);

	// The enemy is going to follow the different steps in the path
	// Position will be updated depending on the speed defined at each step
	void Update() override;

private:
	// A set of steps that define the position in the screen
	// And an animation for each step

	bool alive = true;

	Collider* colliderEnemy = nullptr;

	//animations for the enemy
	Animation* currentanimationlegs;
	Animation Eup, Edown, Eleft, Eright, Eupleft, Eupright, Edownleft, Edownright;
};


#endif // __ENEMY_RED__