#ifndef __ENEMY_BROWNSHIP_H__
#define __ENEMY_BROWNSHIP_H__

#include "Enemy.h"

class Enemy_Truck : public Enemy
{
public:
	// Constructor (x y coordinates in the world)
	// Creates animation and movement data and the collider
	Enemy_Truck(int x, int y);

	// The enemy is going to follow the different steps in the path
	// Position will be updated depending on the speed defined at each step
	void Update() override;


private:
	
	bool alive = true;

	// This enemy has one sprite and one frame
	// We are keeping it an animation for consistency with other enemies
	Animation appear;
	Animation death;
};

#endif // __ENEMY_BROWNSHIP_H__